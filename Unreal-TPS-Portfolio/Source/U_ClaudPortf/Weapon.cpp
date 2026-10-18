// Copyright Epic Games, Inc. All Rights Reserved.

#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "U_ClaudPortfCharacter.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, Log, All);

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

	// Aim from the camera so the shot goes where the player is looking
	const UCameraComponent* Camera = Shooter->GetFollowCamera();
	const FVector TraceStart = Camera->GetComponentLocation();
	const FVector TraceEnd = TraceStart + Camera->GetForwardVector() * FireRange;

	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(WeaponFire), false);
	QueryParams.AddIgnoredActor(Shooter);
	QueryParams.AddIgnoredActor(this);

	FHitResult Hit;
	const bool bHit = World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

	if (bHit)
	{
		UE_LOG(LogWeapon, Log, TEXT("'%s' Hit '%s'"), *GetNameSafe(this), *GetNameSafe(Hit.GetActor()));
		DrawDebugLine(World, TraceStart, Hit.ImpactPoint, FColor::Green, false, 1.f, 0, 1.f);

		// Actors without a TakeDamage override simply ignore this
		UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, Shooter->GetController(), this, UDamageType::StaticClass());
	}
	else
	{
		DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 1.f, 0, 1.f);
	}
}
