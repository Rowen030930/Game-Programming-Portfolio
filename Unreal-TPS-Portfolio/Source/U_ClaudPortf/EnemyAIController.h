// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * Periodically checks the distance to the player and chases them on the NavMesh
 * while they are within DetectionRadius.
 */
UCLASS()
class AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	/** The player is chased while closer than this distance */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float DetectionRadius = 1500.f;

	/**
	 * How close the enemy gets to the player before it stops moving.
	 * The move ends at a 2D center distance of AcceptanceRadius + player capsule radius + 1.1 x enemy capsule radius
	 * (UPathFollowingComponent::HasReached; 60 + 42 + 46.2 = about 148 for the default capsules).
	 * Keep that below AEnemyCharacter::AttackRange or the enemy stops before it can attack.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float AcceptanceRadius = 60.f;

	/** Seconds between distance checks */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true", ClampMin = "0.05"))
	float CheckInterval = 0.25f;

	/** True while the player is inside DetectionRadius */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	bool bIsChasing = false;

	FTimerHandle CheckTimerHandle;

	/** Number of MoveToActor requests that failed in a row */
	int32 ConsecutiveMoveFailures = 0;

	/** True once the "stopped outside AttackRange" warning has been logged */
	bool bWarnedStoppedOutsideAttackRange = false;

public:
	AEnemyAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	/** Starts or stops chasing depending on the distance to the player */
	void CheckPlayerDistance();

	/** Clears the chase state and stops any active move */
	void StopChasing();

public:
	/** Returns true while the player is being chased **/
	FORCEINLINE bool IsChasing() const { return bIsChasing; }
};
