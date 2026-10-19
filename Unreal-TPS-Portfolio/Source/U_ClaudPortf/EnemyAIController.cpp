// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "U_ClaudPortfCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogEnemyAI, Log, All);

/** Consecutive MoveToActor failures (one per distance check) before a warning is logged */
static constexpr int32 MoveFailureWarningThreshold = 4;

AEnemyAIController::AEnemyAIController()
{
	// AAIController::Tick turns the control rotation toward the focus that AEnemyCharacter sets while attacking
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorldTimerManager().SetTimer(CheckTimerHandle, this, &AEnemyAIController::CheckPlayerDistance, CheckInterval, true);
}

void AEnemyAIController::OnUnPossess()
{
	// AEnemyCharacter::Die() unpossesses the pawn, so this is where the AI stops on death
	GetWorldTimerManager().ClearTimer(CheckTimerHandle);
	StopChasing();

	Super::OnUnPossess();
}

void AEnemyAIController::CheckPlayerDistance()
{
	APawn* ControlledPawn = GetPawn();
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(ControlledPawn);
	if (ControlledPawn == nullptr || (Enemy && Enemy->IsDead()))
	{
		StopChasing();
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	const AU_ClaudPortfCharacter* PlayerCharacter = Cast<AU_ClaudPortfCharacter>(PlayerPawn);
	// A dead player is treated as out of range so the enemy neither chases nor attacks it
	const bool bInRange = PlayerPawn != nullptr
		&& !(PlayerCharacter && PlayerCharacter->IsDead())
		&& FVector::DistSquared(ControlledPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= FMath::Square(DetectionRadius);

	if (!bInRange)
	{
		if (bIsChasing)
		{
			UE_LOG(LogEnemyAI, Log, TEXT("'%s' Lost the player"), *GetNameSafe(ControlledPawn));
			StopChasing();
		}
		return;
	}

	const bool bJustDetected = !bIsChasing;
	if (bJustDetected)
	{
		UE_LOG(LogEnemyAI, Log, TEXT("'%s' Detected '%s'"), *GetNameSafe(ControlledPawn), *GetNameSafe(PlayerPawn));
		bIsChasing = true;
	}

	// Within reach: stand still and attack. AEnemyCharacter keeps the attack interval
	if (Enemy && Enemy->IsInAttackRange(PlayerPawn))
	{
		StopMovement();
		Enemy->StartAttacking(PlayerPawn);
		return;
	}

	// Out of reach again: stop attacking and resume the chase
	if (Enemy)
	{
		Enemy->StopAttacking();
	}

	// MoveToActor keeps following a moving goal, but the request ends once the enemy
	// reaches AcceptanceRadius, so issue a new one whenever no move is active
	if (GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		const EPathFollowingRequestResult::Type Result = MoveToActor(PlayerPawn, AcceptanceRadius);
		if (Result == EPathFollowingRequestResult::Failed)
		{
			// A single failure right after PIE starts recovers on the next check, so only warn when it keeps failing
			if (++ConsecutiveMoveFailures == MoveFailureWarningThreshold)
			{
				UE_LOG(LogEnemyAI, Warning, TEXT("'%s' MoveToActor to '%s' failed %d times in a row. See LogAINavigation in the Visual Logger for the reason."), *GetNameSafe(ControlledPawn), *GetNameSafe(PlayerPawn), ConsecutiveMoveFailures);
			}
		}
		else
		{
			ConsecutiveMoveFailures = 0;

			// Only reached while out of attack range, so the move considers the goal reached too early
			if (Result == EPathFollowingRequestResult::AlreadyAtGoal && !bWarnedStoppedOutsideAttackRange)
			{
				UE_LOG(LogEnemyAI, Warning, TEXT("'%s' Stopped next to '%s' but is outside AttackRange. Lower AcceptanceRadius (%.0f) or raise AttackRange."), *GetNameSafe(ControlledPawn), *GetNameSafe(PlayerPawn), AcceptanceRadius);
				bWarnedStoppedOutsideAttackRange = true;
			}
		}
	}
}

void AEnemyAIController::StopChasing()
{
	bIsChasing = false;
	ConsecutiveMoveFailures = 0;
	StopMovement();

	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(GetPawn()))
	{
		Enemy->StopAttacking();
	}
}
