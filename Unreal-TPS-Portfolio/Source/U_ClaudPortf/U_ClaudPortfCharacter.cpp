// Copyright Epic Games, Inc. All Rights Reserved.

#include "U_ClaudPortfCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "AmmoPickup.h"
#include "U_ClaudPortfGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AU_ClaudPortfCharacter

AU_ClaudPortfCharacter::AU_ClaudPortfCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AU_ClaudPortfCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Show the HUD only on the screen of the player controlling this character
		if (PlayerHUDClass && PlayerController->IsLocalController())
		{
			PlayerHUD = CreateWidget<UUserWidget>(PlayerController, PlayerHUDClass);
			if (PlayerHUD)
			{
				PlayerHUD->AddToViewport();
				UpdateAmmoHUD();
				UpdateHealthHUD();
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AU_ClaudPortfCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AU_ClaudPortfCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AU_ClaudPortfCharacter::Look);

		// Equipping
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AU_ClaudPortfCharacter::Equip);

		// Firing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AU_ClaudPortfCharacter::Fire);

		// Reloading
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AU_ClaudPortfCharacter::Reload);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AU_ClaudPortfCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AU_ClaudPortfCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

//////////////////////////////////////////////////////////////////////////
// Weapon

void AU_ClaudPortfCharacter::SetOverlappingWeapon(AWeapon* Weapon)
{
	OverlappingWeapon = Weapon;
}

void AU_ClaudPortfCharacter::Equip()
{
	// Only pick up while a weapon is in range, and only one weapon at a time
	if (OverlappingWeapon == nullptr || EquippedWeapon != nullptr)
	{
		return;
	}

	AWeapon* WeaponToEquip = OverlappingWeapon;
	OverlappingWeapon = nullptr;

	WeaponToEquip->Equip(GetMesh(), WeaponSocketName, this);
	EquippedWeapon = WeaponToEquip;

	// Switch to the rifle stance. There is no unequip, so the unarmed anim class is never restored
	if (ArmedAnimClass)
	{
		GetMesh()->SetAnimInstanceClass(ArmedAnimClass);
	}

	UE_LOG(LogTemplateCharacter, Log, TEXT("'%s' Equipped '%s'"), *GetNameSafe(this), *GetNameSafe(EquippedWeapon));

	UpdateAmmoHUD();

	// Ammo pickups already in range were skipped while unarmed and won't fire a new overlap, so collect them now
	TArray<AActor*> OverlappingPickups;
	GetOverlappingActors(OverlappingPickups, AAmmoPickup::StaticClass());
	for (AActor* Pickup : OverlappingPickups)
	{
		CastChecked<AAmmoPickup>(Pickup)->TryGiveAmmo(this);
	}
}

void AU_ClaudPortfCharacter::Fire()
{
	// Can only fire with a weapon in hand
	if (EquippedWeapon == nullptr)
	{
		return;
	}

	EquippedWeapon->Fire(this);
	UpdateAmmoHUD();
}

void AU_ClaudPortfCharacter::Reload()
{
	// Can only reload a weapon in hand
	if (EquippedWeapon == nullptr)
	{
		return;
	}

	EquippedWeapon->Reload();
	UpdateAmmoHUD();
}

bool AU_ClaudPortfCharacter::AddReserveAmmo(int32 Amount)
{
	// Spare rounds belong to the weapon, so there is nowhere to put them without one in hand
	if (bIsDead || EquippedWeapon == nullptr || !EquippedWeapon->AddReserveAmmo(Amount))
	{
		return false;
	}

	UpdateAmmoHUD();
	return true;
}

void AU_ClaudPortfCharacter::UpdateAmmoHUD()
{
	if (PlayerHUD == nullptr)
	{
		return;
	}

	UTextBlock* AmmoText = Cast<UTextBlock>(PlayerHUD->GetWidgetFromName(AmmoTextName));
	UTextBlock* ReserveAmmoText = Cast<UTextBlock>(PlayerHUD->GetWidgetFromName(ReserveAmmoTextName));
	if (AmmoText == nullptr || ReserveAmmoText == nullptr)
	{
		UE_LOG(LogTemplateCharacter, Warning, TEXT("'%s' HUD '%s' is missing a Text Block named '%s' or '%s'"), *GetNameSafe(this), *GetNameSafe(PlayerHUD), *AmmoTextName.ToString(), *ReserveAmmoTextName.ToString());
		return;
	}

	if (EquippedWeapon)
	{
		AmmoText->SetText(FText::FromString(FString::Printf(TEXT("Ammo: %d / %d"), EquippedWeapon->GetCurrentAmmo(), EquippedWeapon->GetMagazineCapacity())));
		ReserveAmmoText->SetText(FText::FromString(FString::Printf(TEXT("Reserve Ammo: %d"), EquippedWeapon->GetReserveAmmo())));
	}
	else
	{
		AmmoText->SetText(FText::FromString(TEXT("Ammo: - / -")));
		ReserveAmmoText->SetText(FText::FromString(TEXT("Reserve Ammo: -")));
	}
}

void AU_ClaudPortfCharacter::UpdateHealthHUD()
{
	if (PlayerHUD == nullptr)
	{
		return;
	}

	UTextBlock* HealthText = Cast<UTextBlock>(PlayerHUD->GetWidgetFromName(HealthTextName));
	UProgressBar* HealthBar = Cast<UProgressBar>(PlayerHUD->GetWidgetFromName(HealthBarName));
	if (HealthText == nullptr || HealthBar == nullptr)
	{
		UE_LOG(LogTemplateCharacter, Warning, TEXT("'%s' HUD '%s' is missing a Text Block named '%s' or a Progress Bar named '%s'"), *GetNameSafe(this), *GetNameSafe(PlayerHUD), *HealthTextName.ToString(), *HealthBarName.ToString());
	}

	// Round the current health up so a nearly dead player never reads "HP 0"
	if (HealthText)
	{
		HealthText->SetText(FText::FromString(FString::Printf(TEXT("HP %d / %d"), FMath::CeilToInt(CurrentHealth), FMath::RoundToInt(MaxHealth))));
	}

	if (HealthBar)
	{
		const float HealthRatio = MaxHealth > 0.f ? FMath::Clamp(CurrentHealth / MaxHealth, 0.f, 1.f) : 0.f;
		HealthBar->SetPercent(HealthRatio);

		// Green above 50%, yellow above 20%, red at 20% and below
		const TCHAR* FillHex = HealthRatio > 0.5f ? TEXT("38C67A") : (HealthRatio > 0.2f ? TEXT("F5B942") : TEXT("E94F64"));
		HealthBar->SetFillColorAndOpacity(FLinearColor(FColor::FromHex(FillHex)));
	}
}

//////////////////////////////////////////////////////////////////////////
// Health

float AU_ClaudPortfCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// A dead player takes no more damage and never dies twice
	if (bIsDead)
	{
		return 0.f;
	}

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage <= 0.f)
	{
		return 0.f;
	}

	CurrentHealth = FMath::Max(CurrentHealth - ActualDamage, 0.f);
	UE_LOG(LogTemplateCharacter, Log, TEXT("'%s' Took %.1f damage from '%s'. Health: %.1f / %.1f"), *GetNameSafe(this), ActualDamage, *GetNameSafe(DamageCauser), CurrentHealth, MaxHealth);
	UpdateHealthHUD();

	if (CurrentHealth <= 0.f)
	{
		Die();
	}

	return ActualDamage;
}

void AU_ClaudPortfCharacter::Die()
{
	if (bIsDead)
	{
		return;
	}
	bIsDead = true;

	UE_LOG(LogTemplateCharacter, Log, TEXT("'%s' Died"), *GetNameSafe(this));

	StopMovementAndInput();

	if (AU_ClaudPortfGameMode* GameMode = GetWorld()->GetAuthGameMode<AU_ClaudPortfGameMode>())
	{
		GameMode->NotifyPlayerDied();
	}
}

void AU_ClaudPortfCharacter::StopMovementAndInput()
{
	// Stop moving and keep the movement component from moving the actor again
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	// Removes this pawn's input component from the controller, which stops Move/Look/Jump/Equip/Fire/Reload
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		DisableInput(PlayerController);
	}
}

//////////////////////////////////////////////////////////////////////////
// Game result

void AU_ClaudPortfCharacter::HandleGameEnded(bool bVictory)
{
	StopMovementAndInput();

	// Free the mouse so the result widget's buttons can be clicked
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->SetShowMouseCursor(true);
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}

	if (bVictory)
	{
		OnVictory();
	}
	else
	{
		OnGameOver();
	}
}