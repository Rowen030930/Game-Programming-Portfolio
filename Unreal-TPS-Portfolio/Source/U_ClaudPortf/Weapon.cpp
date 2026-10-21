// Copyright Epic Games, Inc. All Rights Reserved.

#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "U_ClaudPortfCharacter.h"
#include "EnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, Log, All);

/** Seconds the bDrawFireDebug shapes stay on screen */
static constexpr float FireDebugDuration = 2.f;

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	// Mesh is the root so the whole actor snaps to the socket when equipped
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	// Don't block the player or pull in the camera boom while lying on the ground
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// Pickup range only reacts to pawns
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetupAttachment(WeaponMesh);
	PickupSphere->InitSphereRadius(100.f);
	// Keep the radius independent of the mesh scale used for placeholder meshes
	PickupSphere->SetUsingAbsoluteScale(true);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MagazineCapacity;

	// Report a missing muzzle socket when play starts instead of on the first shot
	if (!WeaponMesh->DoesSocketExist(MuzzleSocketName))
	{
		bWarnedMissingMuzzleSocket = true;
		UE_LOG(LogWeapon, Warning, TEXT("'%s' Weapon mesh '%s' has no socket named '%s'. Shots will start from the mesh's origin instead of the muzzle"), *GetNameSafe(this), *GetNameSafe(WeaponMesh->GetStaticMesh()), *MuzzleSocketName.ToString());
	}

	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereBeginOverlap);
	PickupSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);
}

void AWeapon::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AU_ClaudPortfCharacter* Character = Cast<AU_ClaudPortfCharacter>(OtherActor))
	{
		Character->SetOverlappingWeapon(this);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AU_ClaudPortfCharacter* Character = Cast<AU_ClaudPortfCharacter>(OtherActor))
	{
		// Only clear the reference if it still points to this weapon
		if (Character->GetOverlappingWeapon() == this)
		{
			Character->SetOverlappingWeapon(nullptr);
		}
	}
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner)
{
	if (InParent == nullptr)
	{
		return;
	}

	PickupSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!InParent->DoesSocketExist(InSocketName))
	{
		UE_LOG(LogWeapon, Warning, TEXT("'%s' Socket '%s' not found on '%s'. Weapon will attach to the component origin."), *GetNameSafe(this), *InSocketName.ToString(), *GetNameSafe(InParent));
	}

	SetOwner(NewOwner);
	AttachToComponent(InParent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InSocketName);
}

void AWeapon::Fire(AU_ClaudPortfCharacter* Shooter)
{
	if (Shooter == nullptr || Shooter->GetFollowCamera() == nullptr)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}

	if (CurrentAmmo <= 0)
	{
		UE_LOG(LogWeapon, Log, TEXT("'%s' Magazine is empty. Reserve: %d"), *GetNameSafe(this), ReserveAmmo);
		return;
	}
	--CurrentAmmo;
	UE_LOG(LogWeapon, Log, TEXT("'%s' Fired. Ammo: %d / %d, Reserve: %d"), *GetNameSafe(this), CurrentAmmo, MagazineCapacity, ReserveAmmo);

	// Sound and muzzle flash are played by the Blueprint, for hits and misses alike
	const bool bHasMuzzleSocket = WeaponMesh->DoesSocketExist(MuzzleSocketName);
	if (!bHasMuzzleSocket && !bWarnedMissingMuzzleSocket)
	{
		bWarnedMissingMuzzleSocket = true;
		UE_LOG(LogWeapon, Warning, TEXT("'%s' Weapon mesh '%s' has no socket named '%s'. OnWeaponFired gets the mesh's own transform instead of the muzzle's"), *GetNameSafe(this), *GetNameSafe(WeaponMesh->GetStaticMesh()), *MuzzleSocketName.ToString());
	}
	const FTransform MuzzleTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
	OnWeaponFired(MuzzleTransform, bHasMuzzleSocket);

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(WeaponFire), false);
	QueryParams.AddIgnoredActor(Shooter);
	QueryParams.AddIgnoredActor(this);

	// 1st trace (camera): only decides where the player is aiming, never what gets hit
	FVector AimStart;
	FHitResult AimHit;
	const FVector AimPoint = TraceAimPoint(Shooter, QueryParams, AimStart, AimHit);

	// 2nd trace (muzzle): the bullet leaves the barrel, so cover between the muzzle and the aim point blocks the shot.
	// It runs the full FireRange toward the aim point so it doesn't stop just short of the aimed surface
	const FVector CameraForward = Shooter->GetFollowCamera()->GetForwardVector();
	const FVector MuzzleLocation = MuzzleTransform.GetLocation();
	FVector ShotDirection = (AimPoint - MuzzleLocation).GetSafeNormal();
	// An aim point level with or behind the muzzle (e.g. when hugging a wall) would send the shot sideways or backward
	if (FVector::DotProduct(ShotDirection, CameraForward) <= 0.f)
	{
		ShotDirection = CameraForward;
	}
	const FVector ShotEnd = MuzzleLocation + ShotDirection * FireRange;

	FHitResult Hit;
	const bool bHit = World->LineTraceSingleByChannel(Hit, MuzzleLocation, ShotEnd, ECC_Visibility, QueryParams);

	if (bHit)
	{
		UE_LOG(LogWeapon, Log, TEXT("'%s' Hit '%s'"), *GetNameSafe(this), *GetNameSafe(Hit.GetActor()));
		if (AimHit.bBlockingHit && AimHit.GetActor() != Hit.GetActor())
		{
			UE_LOG(LogWeapon, Log, TEXT("'%s' Shot aimed at '%s' was blocked by '%s'"), *GetNameSafe(this), *GetNameSafe(AimHit.GetActor()), *GetNameSafe(Hit.GetActor()));
		}

		// Enemies take damage by hit location; other actors take Damage (actors without a TakeDamage override simply ignore it)
		float ShotDamage = Damage;
		if (const AEnemyCharacter* HitEnemy = Cast<AEnemyCharacter>(Hit.GetActor()))
		{
			const bool bHeadshot = HitEnemy->IsHeadHit(Hit);
			ShotDamage = bHeadshot ? EnemyHeadshotDamage : EnemyBodyDamage;
			UE_LOG(LogWeapon, Log, TEXT("'%s' %s on '%s' (bone '%s') for %.1f damage"), *GetNameSafe(this), bHeadshot ? TEXT("Headshot") : TEXT("Body hit"), *GetNameSafe(HitEnemy), *Hit.BoneName.ToString(), ShotDamage);
		}
		UGameplayStatics::ApplyDamage(Hit.GetActor(), ShotDamage, Shooter->GetController(), this, UDamageType::StaticClass());

		// Body impact only on enemies, world impact only on non-characters, so each shot spawns at most one effect
		if (Cast<AEnemyCharacter>(Hit.GetActor()))
		{
			if (EnemyImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(World, EnemyImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}
		}
		else if (WorldImpactEffect && !Cast<ACharacter>(Hit.GetActor()))
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, WorldImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
	}

	if (bDrawFireDebug)
	{
		DrawDebugLine(World, AimStart, AimPoint, FColor::Blue, false, FireDebugDuration, 0, 0.5f);
		DrawDebugSphere(World, AimPoint, 8.f, 8, FColor::Blue, false, FireDebugDuration);
		DrawDebugSphere(World, MuzzleLocation, 5.f, 8, FColor::Yellow, false, FireDebugDuration);
		DrawDebugLine(World, MuzzleLocation, bHit ? Hit.ImpactPoint : ShotEnd, bHit ? FColor::Green : FColor::Red, false, FireDebugDuration, 0, 1.f);
		if (bHit)
		{
			DrawDebugSphere(World, Hit.ImpactPoint, 12.f, 8, FColor::Orange, false, FireDebugDuration);
		}
	}
}

FVector AWeapon::TraceAimPoint(const AU_ClaudPortfCharacter* Shooter, const FCollisionQueryParams& QueryParams, FVector& OutAimStart, FHitResult& OutAimHit) const
{
	const UCameraComponent* Camera = Shooter->GetFollowCamera();
	const FVector CameraLocation = Camera->GetComponentLocation();
	const FVector CameraForward = Camera->GetForwardVector();

	// Move the start along the camera's view up to the shooter's depth. Objects between the camera and the shooter
	// would otherwise become the aim point, while everything farther than the shooter is still traced
	const float ShooterDepth = FMath::Max(FVector::DotProduct(Shooter->GetActorLocation() - CameraLocation, CameraForward), 0.f);
	OutAimStart = CameraLocation + CameraForward * ShooterDepth;
	const FVector AimEnd = CameraLocation + CameraForward * FireRange;

	if (GetWorld()->LineTraceSingleByChannel(OutAimHit, OutAimStart, AimEnd, ECC_Visibility, QueryParams))
	{
		return OutAimHit.ImpactPoint;
	}
	return AimEnd;
}

void AWeapon::Reload()
{
	if (CurrentAmmo >= MagazineCapacity)
	{
		UE_LOG(LogWeapon, Log, TEXT("'%s' Magazine is already full"), *GetNameSafe(this));
		return;
	}

	if (ReserveAmmo <= 0)
	{
		UE_LOG(LogWeapon, Log, TEXT("'%s' No reserve ammo to reload"), *GetNameSafe(this));
		return;
	}

	// Only move the rounds the magazine is missing
	const int32 RoundsToLoad = FMath::Min(MagazineCapacity - CurrentAmmo, ReserveAmmo);
	CurrentAmmo += RoundsToLoad;
	ReserveAmmo -= RoundsToLoad;

	UE_LOG(LogWeapon, Log, TEXT("'%s' Reloaded %d rounds. Ammo: %d / %d, Reserve: %d"), *GetNameSafe(this), RoundsToLoad, CurrentAmmo, MagazineCapacity, ReserveAmmo);
}

bool AWeapon::AddReserveAmmo(int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	ReserveAmmo += Amount;
	UE_LOG(LogWeapon, Log, TEXT("'%s' Got %d spare rounds. Ammo: %d / %d, Reserve: %d"), *GetNameSafe(this), Amount, CurrentAmmo, MagazineCapacity, ReserveAmmo);
	return true;
}
