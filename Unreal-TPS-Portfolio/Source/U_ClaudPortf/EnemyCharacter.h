// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Health the enemy starts with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true", ClampMin = "1.0"))
	float MaxHealth = 100.f;

	/** Remaining health; the enemy dies when this reaches 0 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.f;

	/** True once Die() has run; further damage is ignored */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	/** Seconds the ragdoll stays in the level before the actor is removed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float DeathLifeSpan = 5.f;

public:
	AEnemyCharacter();

	/** Reduces CurrentHealth and calls Die() when it runs out */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

	/** Stops movement, releases the controller and capsule, and switches the mesh to ragdoll */
	void Die();

public:
	/** Returns the maximum health **/
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	/** Returns the remaining health **/
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	/** Returns true once the enemy has died **/
	FORCEINLINE bool IsDead() const { return bIsDead; }
};
