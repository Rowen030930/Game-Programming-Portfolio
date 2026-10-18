// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetDummy.generated.h"

class UStaticMeshComponent;

UCLASS()
class ATargetDummy : public AActor
{
	GENERATED_BODY()

	/** Target mesh; must block the Visibility channel to be hit by weapon traces */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TargetMesh;

	/** Health the target starts with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true", ClampMin = "1.0"))
	float MaxHealth = 100.f;

	/** Remaining health; the target is destroyed when this reaches 0 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.f;

public:
	ATargetDummy();

	/** Reduces CurrentHealth and destroys the target when it runs out */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

public:
	/** Returns TargetMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetTargetMesh() const { return TargetMesh; }
	/** Returns the maximum health **/
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	/** Returns the remaining health **/
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
};
