// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "U_ClaudPortfCharacter.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogEnemy, Log, All);

/** Seconds between checks while waiting to face the target before a swing */
static constexpr float AttackFacingRetryInterval = 0.1f;

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Same capsule size as the player character
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Both the Pawn capsule and the CharacterMesh profile ignore Visibility,
	// so let the mesh's physics bodies block the trace used by AWeapon::Fire
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// The kick hit test reads the foot bone positions, so keep them up to date even when the enemy is off screen
	// (ACharacter's default AlwaysTickPose skips refreshing bones of meshes that aren't rendered)
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	// Chase the player with AEnemyAIController, whether placed in the level or spawned at runtime
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Face the direction of movement while chasing instead of the controller's rotation
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Slower than the player's 500 so the enemy turns toward the player less abruptly
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);

	// Chase a bit slower than the player (500) so they can get away. Tweak Max Walk Speed on BP_EnemyCharacter's Character Movement
	GetCharacterMovement()->MaxWalkSpeed = 350.f;

	// Let path following steer through acceleration so the velocity turns gradually at path corners instead of snapping.
	// bUseAccelerationForPaths is a protected UPROPERTY of UNavMovementComponent with no setter in UE 5.3, so set it via reflection
	FBoolProperty* UseAccelerationForPathsProperty = FindFProperty<FBoolProperty>(UNavMovementComponent::StaticClass(), TEXT("bUseAccelerationForPaths"));
	if (ensureMsgf(UseAccelerationForPathsProperty, TEXT("UNavMovementComponent::bUseAccelerationForPaths not found")))
	{
		UseAccelerationForPathsProperty->SetPropertyValue_InContainer(GetCharacterMovement(), true);
	}

	// Note: The skeletal mesh and anim blueprint are set in the derived blueprint (BP_EnemyCharacter)
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	// Remember the chase rotation settings (including Blueprint overrides) that SetFacingAttackTarget(false) restores
	bChaseOrientRotationToMovement = GetCharacterMovement()->bOrientRotationToMovement;
	bChaseUseControllerDesiredRotation = GetCharacterMovement()->bUseControllerDesiredRotation;

	// Fired by "Montage Notify" entries in any montage this mesh plays; OnMontageNotifyBegin filters for the hit notify
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AEnemyCharacter::OnMontageNotifyBegin);
	}
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Dead enemies take no more damage and never die twice
	if (bIsDead)
	{
		return 0.f;
	}

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage <= 0.f)
	{
		return 0.f;
	}

	CurrentHealth = FMath::Max(CurrentHealth - ActualDamage, 0.f);
	UE_LOG(LogEnemy, Log, TEXT("'%s' Took %.1f damage from '%s'. Health: %.1f / %.1f"), *GetNameSafe(this), ActualDamage, *GetNameSafe(DamageCauser), CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.f)
	{
		Die();
	}

	return ActualDamage;
}

void AEnemyCharacter::Die()
{
	if (bIsDead)
	{
		return;
	}
	bIsDead = true;

	UE_LOG(LogEnemy, Log, TEXT("'%s' Died"), *GetNameSafe(this));

	StopAttacking();

	// Stop moving and keep the movement component from moving the actor again
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	// Unpossess and destroy the (AI) controller so nothing drives this pawn anymore
	DetachFromControllerPendingDestroy();

	// Let the player walk through the body
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Ragdoll using the mesh's Physics Asset
	USkeletalMeshComponent* MeshComp = GetMesh();
	MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
	MeshComp->SetAllBodiesSimulatePhysics(true);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->WakeAllRigidBodies();
	MeshComp->bBlendPhysics = true;

	SetLifeSpan(DeathLifeSpan);
}

bool AEnemyCharacter::IsInAttackRange(const AActor* Target) const
{
	return Target != nullptr
		&& FVector::DistSquared(GetActorLocation(), Target->GetActorLocation()) <= FMath::Square(AttackRange);
}

bool AEnemyCharacter::IsFacing(const AActor* Target, float MaxAngle) const
{
	const FVector ToTarget = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
	// A target right on top of the enemy counts as in front
	if (ToTarget.IsZero())
	{
		return true;
	}

	return FVector::DotProduct(GetActorForwardVector().GetSafeNormal2D(), ToTarget) >= FMath::Cos(FMath::DegreesToRadians(MaxAngle));
}

bool AEnemyCharacter::HasLineOfSightTo(const AActor* Target) const
{
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(EnemyAttackLineOfSight), false, this);
	QueryParams.AddIgnoredActor(Target);

	// Actors attached to the target (e.g. the player's weapon) are part of it, not cover
	TArray<AActor*> TargetAttachedActors;
	Target->GetAttachedActors(TargetAttachedActors);
	QueryParams.AddIgnoredActors(TargetAttachedActors);

	return !GetWorld()->LineTraceTestByChannel(GetActorLocation(), Target->GetActorLocation(), ECC_Visibility, QueryParams);
}

bool AEnemyCharacter::IsKickTouching(const AActor* Target) const
{
	const USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp->GetBoneIndex(KickFootBone) == INDEX_NONE || MeshComp->GetBoneIndex(KickTipBone) == INDEX_NONE)
	{
		UE_LOG(LogEnemy, Warning, TEXT("'%s' Mesh '%s' has no bone '%s' or '%s', so the kick can't hit. Set KickFootBone/KickTipBone to bones of its skeleton"),
			*GetNameSafe(this), *GetNameSafe(MeshComp->GetSkinnedAsset()), *KickFootBone.ToString(), *KickTipBone.ToString());
		return false;
	}

	// The target's root collision, i.e. the player's capsule
	const UPrimitiveComponent* TargetCollision = Cast<UPrimitiveComponent>(Target->GetRootComponent());
	if (TargetCollision == nullptr)
	{
		return false;
	}

	// A capsule from the foot to its tip is the shape a sphere of KickHitRadius sweeps along the foot
	const FVector FootLocation = MeshComp->GetBoneLocation(KickFootBone);
	const FVector TipLocation = MeshComp->GetBoneLocation(KickTipBone);
	const FVector FootToTip = TipLocation - FootLocation;
	const FVector HitCenter = (FootLocation + TipLocation) * 0.5f;
	const FQuat HitRotation = FootToTip.IsNearlyZero() ? FQuat::Identity : FRotationMatrix::MakeFromZ(FootToTip).ToQuat();
	const float HitHalfHeight = FootToTip.Size() * 0.5f + KickHitRadius;

	const bool bTouching = TargetCollision->OverlapComponent(HitCenter, HitRotation, FCollisionShape::MakeCapsule(KickHitRadius, HitHalfHeight));

	if (bDrawKickHitDebug)
	{
		DrawDebugCapsule(GetWorld(), HitCenter, HitHalfHeight, KickHitRadius, HitRotation, bTouching ? FColor::Green : FColor::Red, false, 2.f);
	}

	return bTouching;
}

void AEnemyCharacter::SetFacingAttackTarget(bool bFace)
{
	// The enemy stands still while attacking, so bOrientRotationToMovement never turns it toward a target circling around it.
	// Turn toward the AI controller's focus instead (same RotationRate), and go back to facing the movement direction for the chase
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->bOrientRotationToMovement = bFace ? false : bChaseOrientRotationToMovement;
	MoveComp->bUseControllerDesiredRotation = bFace ? true : bChaseUseControllerDesiredRotation;

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (bFace)
		{
			AIController->SetFocus(AttackTarget);
		}
		else
		{
			AIController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}

void AEnemyCharacter::StartAttacking(AActor* Target)
{
	if (bIsDead || Target == nullptr || Target == AttackTarget)
	{
		return;
	}

	AttackTarget = Target;
	SetFacingAttackTarget(true);

	// Keep the interval between attacks even if the target left and came back in range
	const double Now = GetWorld()->GetTimeSeconds();
	const double RemainingCooldown = LastAttackTime < 0.0 ? 0.0 : FMath::Max(LastAttackTime + AttackInterval - Now, 0.0);

	if (RemainingCooldown <= 0.0)
	{
		PerformAttack();
	}
	else
	{
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::PerformAttack, RemainingCooldown, false);
	}
}

void AEnemyCharacter::StopAttacking()
{
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	AttackTarget = nullptr;
	SetFacingAttackTarget(false);

	// Cancel a swing in progress so its hit notify can't apply damage later
	bAttackHitPending = false;
	if (AttackMontage)
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Stop(0.2f, AttackMontage);
		}
	}
}

void AEnemyCharacter::PerformAttack()
{
	const AU_ClaudPortfCharacter* Player = Cast<AU_ClaudPortfCharacter>(AttackTarget);
	if (bIsDead || !IsValid(AttackTarget) || (Player && Player->IsDead()))
	{
		StopAttacking();
		return;
	}

	// Melee hit check: the swing only lands if the target is still within reach.
	// Otherwise skip this swing and let the AI controller decide whether to chase again
	if (!IsInAttackRange(AttackTarget))
	{
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::PerformAttack, AttackInterval, false);
		return;
	}

	// Don't kick into the air: wait for the turn toward the target (SetFacingAttackTarget) to bring it in front
	if (!IsFacing(AttackTarget, AttackStartAngle))
	{
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::PerformAttack, AttackFacingRetryInterval, false);
		return;
	}

	LastAttackTime = GetWorld()->GetTimeSeconds();
	// Schedule the next swing before this one can stop attacking (ApplyAttackDamage() clears the timer if the target dies)
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::PerformAttack, AttackInterval, false);

	// The previous swing ended without its hit notify: the montage is probably missing it
	if (bAttackHitPending && !bWarnedMissingHitNotify)
	{
		UE_LOG(LogEnemy, Warning, TEXT("'%s' AttackMontage '%s' finished without a Montage Notify named '%s', so it dealt no damage"), *GetNameSafe(this), *GetNameSafe(AttackMontage), *AttackHitNotifyName.ToString());
		bWarnedMissingHitNotify = true;
	}
	bAttackHitPending = false;

	// Play the swing and wait for its hit notify. Fall back to instant damage without a playable montage
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AttackMontage && AnimInstance && AnimInstance->Montage_Play(AttackMontage) > 0.f)
	{
		// Play only the AttackStart section: start there, and end at the next section marker (AttackEnd)
		// instead of following the section links the montage editor creates, which would play the rest of the animation
		const FName AttackStartSection(TEXT("AttackStart"));
		AnimInstance->Montage_JumpToSection(AttackStartSection, AttackMontage);
		AnimInstance->Montage_SetNextSection(AttackStartSection, NAME_None, AttackMontage);
		bAttackHitPending = true;
		return;
	}

	ApplyAttackDamage();
}

void AEnemyCharacter::ApplyAttackDamage()
{
	// Re-check at the moment of impact: the target may have died or stepped away during the swing
	const AU_ClaudPortfCharacter* Player = Cast<AU_ClaudPortfCharacter>(AttackTarget);
	if (bIsDead || !IsValid(AttackTarget) || (Player && Player->IsDead()))
	{
		return;
	}

	// The kick must actually point at the target and not pass through a wall
	if (!IsFacing(AttackTarget, AttackHitAngle) || !HasLineOfSightTo(AttackTarget))
	{
		UE_LOG(LogEnemy, Log, TEXT("'%s' Missed '%s' (not in front or behind cover)"), *GetNameSafe(this), *GetNameSafe(AttackTarget));
		return;
	}

	// Instead of the center distance, the kicking foot itself has to reach the target
	if (!IsKickTouching(AttackTarget))
	{
		UE_LOG(LogEnemy, Log, TEXT("'%s' Missed '%s' (the kick didn't reach it)"), *GetNameSafe(this), *GetNameSafe(AttackTarget));
		return;
	}

	UE_LOG(LogEnemy, Log, TEXT("'%s' Attacked '%s' for %.1f damage"), *GetNameSafe(this), *GetNameSafe(AttackTarget), AttackDamage);
	const float AppliedDamage = UGameplayStatics::ApplyDamage(AttackTarget, AttackDamage, GetController(), this, UDamageType::StaticClass());

	// The hit may have killed the target
	if (Player && Player->IsDead())
	{
		StopAttacking();
		return;
	}

	// Push a surviving character target a short way back. A dead player is skipped above:
	// launching would switch its disabled movement back to Falling
	ACharacter* TargetCharacter = Cast<ACharacter>(AttackTarget);
	if (AppliedDamage > 0.f && TargetCharacter && KnockbackStrength > 0.f)
	{
		FVector KnockbackDirection = (TargetCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
		if (KnockbackDirection.IsZero())
		{
			KnockbackDirection = GetActorForwardVector().GetSafeNormal2D();
		}

		// Override the target's current velocity so the push is the same whether it was running toward or away from the enemy
		TargetCharacter->LaunchCharacter(KnockbackDirection * KnockbackStrength + FVector(0.f, 0.f, KnockbackUpwardSpeed), true, true);
	}
}

void AEnemyCharacter::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (!bAttackHitPending || NotifyName != AttackHitNotifyName)
	{
		return;
	}

	bAttackHitPending = false;
	ApplyAttackDamage();
}
