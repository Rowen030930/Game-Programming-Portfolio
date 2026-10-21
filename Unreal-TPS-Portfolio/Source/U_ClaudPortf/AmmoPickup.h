// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoPickup.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AU_ClaudPortfCharacter;

UCLASS()
class AAmmoPickup : public AActor
{
	GENERATED_BODY()

	/** Pickup mesh (a cube); set its Static Mesh in BP_AmmoPickup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;

	/** Collection range; the player picks the ammo up on entering it. Its Sphere Radius is editable in the Details panel */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	USphereComponent* PickupSphere;

	/** Spare rounds added to the player's equipped weapon's ReserveAmmo */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true", ClampMin = "1"))
	int32 AmmoAmount = 30;

	/** True once the ammo has been given; the pickup is being destroyed and gives nothing more */
	bool bPickedUp = false;

public:
	AAmmoPickup();

	/**
	 * Gives AmmoAmount spare rounds to Player and destroys this pickup.
	 * Nothing happens (and the pickup stays) if the player can't take them, e.g. with no weapon in hand
	 */
	void TryGiveAmmo(AU_ClaudPortfCharacter* Player);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	/** Returns PickupMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetPickupMesh() const { return PickupMesh; }
	/** Returns PickupSphere subobject **/
	FORCEINLINE USphereComponent* GetPickupSphere() const { return PickupSphere; }
};
