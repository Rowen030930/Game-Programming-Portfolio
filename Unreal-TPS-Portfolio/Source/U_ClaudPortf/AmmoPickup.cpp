// Copyright Epic Games, Inc. All Rights Reserved.

#include "AmmoPickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "U_ClaudPortfCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, Log, All);

AAmmoPickup::AAmmoPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	// Mesh is the root so the pickup is placed by its mesh
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	SetRootComponent(PickupMesh);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupMesh->SetCollisionResponseToAllChannels(ECR_Block);
	// Let pawns walk into the pickup range instead of bumping into the cube, and keep the camera boom from pulling in
	PickupMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	PickupMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// Pickup range only reacts to pawns; which pawn may collect is decided in OnSphereBeginOverlap
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->SetupAttachment(PickupMesh);
	PickupSphere->InitSphereRadius(100.f);
	// Keep the radius independent of the mesh scale used to size the cube
	PickupSphere->SetUsingAbsoluteScale(true);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();

	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPickup::OnSphereBeginOverlap);
}

void AAmmoPickup::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only the player character collects ammo; enemies (AEnemyCharacter) aren't one
	if (AU_ClaudPortfCharacter* Player = Cast<AU_ClaudPortfCharacter>(OtherActor))
	{
		TryGiveAmmo(Player);
	}
}

void AAmmoPickup::TryGiveAmmo(AU_ClaudPortfCharacter* Player)
{
	// Several of the player's components can overlap in the same frame; only the first one collects
	if (bPickedUp || Player == nullptr)
	{
		return;
	}

	if (!Player->AddReserveAmmo(AmmoAmount))
	{
		UE_LOG(LogAmmoPickup, Log, TEXT("'%s' '%s' can't take ammo (no weapon in hand or dead); the pickup stays"), *GetNameSafe(this), *GetNameSafe(Player));
		return;
	}

	bPickedUp = true;
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UE_LOG(LogAmmoPickup, Log, TEXT("'%s' Gave %d spare rounds to '%s'"), *GetNameSafe(this), AmmoAmount, *GetNameSafe(Player));
	Destroy();
}
