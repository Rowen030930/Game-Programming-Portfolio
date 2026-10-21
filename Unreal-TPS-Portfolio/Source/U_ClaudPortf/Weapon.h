// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UParticleSystem;
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

	/** Damage applied per shot to a hit actor that isn't an AEnemyCharacter */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	float Damage = 25.f;

	/** Damage applied per shot to an AEnemyCharacter hit anywhere but the head */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float EnemyBodyDamage = 10.f;

	/** Damage applied per shot to an AEnemyCharacter hit on the head (AEnemyCharacter::HeadBoneName) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float EnemyHeadshotDamage = 40.f;

	/** Socket on WeaponMesh at the barrel's tip, passed to OnWeaponFired. The mesh needs this socket for a real muzzle position */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName MuzzleSocketName = TEXT("Muzzle");

	/** True once the "missing muzzle socket" warning has been logged */
	bool bWarnedMissingMuzzleSocket = false;

	/** Draws each shot for a few seconds: blue = camera aim trace and aim point, yellow = muzzle, green/red = muzzle trace hit/miss, orange = actual impact point */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bDrawFireDebug = true;

	/** Particle spawned where a shot hits an AEnemyCharacter, facing out of the hit surface. Nothing is spawned when unset or when anything else is hit */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* EnemyImpactEffect = nullptr;

	/** Particle spawned where a shot hits anything that isn't a character (walls, floors, props), facing out of the hit surface. Nothing is spawned when unset or on a miss */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* WorldImpactEffect = nullptr;

	/** Rounds a full magazine holds; the weapon starts with a full magazine */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ammo, meta = (AllowPrivateAccess = "true", ClampMin = "1"))
	int32 MagazineCapacity = 12;

	/** Rounds left in the magazine; each shot uses one */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Ammo, meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo = 0;

	/** Spare rounds that Reload() moves into the magazine */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ammo, meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int32 ReserveAmmo = 36;

public:
	AWeapon();

	/** Disables collision and attaches this weapon to the given socket of InParent */
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner);

	/**
	 * Uses one round and fires in two line traces: one from the shooter's follow camera finds the aim point under the crosshair,
	 * then one from the muzzle toward that point decides what is actually hit, so cover in front of the muzzle blocks the shot.
	 * Does nothing with an empty magazine
	 */
	void Fire(AU_ClaudPortfCharacter* Shooter);

	/** Fills the magazine from ReserveAmmo. Does nothing if the magazine is full or there is no reserve */
	void Reload();

	/** Adds Amount spare rounds to ReserveAmmo without touching the magazine. Returns false (and adds nothing) if Amount isn't positive */
	bool AddReserveAmmo(int32 Amount);

protected:
	virtual void BeginPlay() override;

	/**
	 * Line traces along the shooter's follow camera and returns the point under the crosshair: the impact point, or the end of FireRange on a miss.
	 * The trace starts level with the shooter rather than at the camera, so objects between the camera and the shooter are skipped
	 * @param OutAimStart	Where the trace started
	 * @param OutAimHit		The trace's hit; bBlockingHit is false on a miss
	 */
	FVector TraceAimPoint(const AU_ClaudPortfCharacter* Shooter, const FCollisionQueryParams& QueryParams, FVector& OutAimStart, FHitResult& OutAimHit) const;

	/**
	 * Called once per shot that uses a round, whether or not it hits anything. Implement in the Blueprint to play the shot's sound and muzzle flash.
	 * @param MuzzleTransform	World transform of MuzzleSocketName on WeaponMesh, or of WeaponMesh itself if the socket is missing
	 * @param bHasMuzzleSocket	False if WeaponMesh has no MuzzleSocketName socket, so MuzzleTransform is not the barrel's tip
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void OnWeaponFired(const FTransform& MuzzleTransform, bool bHasMuzzleSocket);

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/** Returns WeaponMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	/** Returns PickupSphere subobject **/
	FORCEINLINE USphereComponent* GetPickupSphere() const { return PickupSphere; }
	/** Returns the rounds a full magazine holds **/
	FORCEINLINE int32 GetMagazineCapacity() const { return MagazineCapacity; }
	/** Returns the rounds left in the magazine **/
	FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }
	/** Returns the spare rounds **/
	FORCEINLINE int32 GetReserveAmmo() const { return ReserveAmmo; }
};
