// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AU_ClaudPortfCharacter;

UCLASS()
class AWeapon : public AActor
{
	GENERATED_BODY()

	/** Weapon mesh shown on the ground and in the character's hand */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WeaponMesh;

	/** Pickup range; overlapping it lets the player equip this weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	USphereComponent* PickupSphere;

	/** Maximum distance of the fire line trace */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float FireRange = 10000.f;

	/** Damage applied to the hit actor per shot */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float Damage = 25.f;

public:
	AWeapon();

	/** Disables collision and attaches this weapon to the given socket of InParent */
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner);

	/** Line traces from the shooter's follow camera along its forward direction and draws the result */
	void Fire(AU_ClaudPortfCharacter* Shooter);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/** Returns WeaponMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	/** Returns PickupSphere subobject **/
	FORCEINLINE USphereComponent* GetPickupSphere() const { return PickupSphere; }
};
