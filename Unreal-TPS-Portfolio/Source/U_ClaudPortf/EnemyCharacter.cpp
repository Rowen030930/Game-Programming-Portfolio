// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogEnemy, Log, All);

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Same capsule size as the player character
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Both the Pawn capsule and the CharacterMesh profile ignore Visibility,
	// so let the mesh's physics bodies block the trace used by AWeapon::Fire
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// Note: The skeletal mesh and anim blueprint are set in the derived blueprint (BP_EnemyCharacter)
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
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
