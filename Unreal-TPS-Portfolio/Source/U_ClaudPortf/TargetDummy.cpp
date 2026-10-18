// Copyright Epic Games, Inc. All Rights Reserved.

#include "TargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"

DEFINE_LOG_CATEGORY_STATIC(LogTargetDummy, Log, All);

ATargetDummy::ATargetDummy()
{
	PrimaryActorTick.bCanEverTick = false;

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	SetRootComponent(TargetMesh);
	// BlockAllDynamic blocks the Visibility channel used by AWeapon::Fire
	TargetMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
}

void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

float ATargetDummy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// Ignore hits that land after the target has already been destroyed
	if (ActualDamage <= 0.f || CurrentHealth <= 0.f)
	{
		return 0.f;
	}

	CurrentHealth = FMath::Max(CurrentHealth - ActualDamage, 0.f);
	UE_LOG(LogTargetDummy, Log, TEXT("'%s' Took %.1f damage from '%s'. Health: %.1f / %.1f"), *GetNameSafe(this), ActualDamage, *GetNameSafe(DamageCauser), CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.f)
	{
		UE_LOG(LogTargetDummy, Log, TEXT("'%s' Destroyed"), *GetNameSafe(this));
		Destroy();
	}

	return ActualDamage;
}
