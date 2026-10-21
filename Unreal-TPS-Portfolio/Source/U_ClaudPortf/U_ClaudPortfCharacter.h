// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "U_ClaudPortfCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AWeapon;
class UUserWidget;
class UAnimInstance;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AU_ClaudPortfCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Equip Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	/** Socket on the character mesh that the equipped weapon attaches to */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	FName WeaponSocketName = TEXT("WeaponSocket");

	/** Weapon currently in pickup range */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeapon* OverlappingWeapon;

	/** Weapon currently held in hand */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;

	/** Anim class the mesh switches to once a weapon is equipped (ABP_RiflePlayer). The unarmed one is the Anim Class set on the Mesh component; left unset, equipping keeps it */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UAnimInstance> ArmedAnimClass;

	/** Widget created and added to the screen at BeginPlay (WBP_PlayerHUD) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayerHUDClass;

	/** Name of the Text Block in PlayerHUDClass that shows the magazine ammo */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	FName AmmoTextName = TEXT("TXT_Ammo");

	/** Name of the Text Block in PlayerHUDClass that shows the reserve ammo */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	FName ReserveAmmoTextName = TEXT("TXT_ReserveAmmo");

	/** Name of the Text Block in PlayerHUDClass that shows "HP current / max" */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	FName HealthTextName = TEXT("TXT_PlayerHealth");

	/** Name of the Progress Bar in PlayerHUDClass whose Percent and fill color show CurrentHealth / MaxHealth */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	FName HealthBarName = TEXT("PB_PlayerHealth");

	/** HUD widget created from PlayerHUDClass; null without a class or a local player controller */
	UPROPERTY(Transient, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> PlayerHUD;

	/** Health the player starts with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true", ClampMin = "1.0"))
	float MaxHealth = 100.f;

	/** Remaining health; the player dies when this reaches 0 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.f;

	/** True once Die() has run; further damage is ignored */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

public:
	AU_ClaudPortfCharacter();

	/** Called by AWeapon when the character enters (Weapon) or leaves (nullptr) its pickup range */
	void SetOverlappingWeapon(AWeapon* Weapon);

	/** Reduces CurrentHealth and calls Die() when it runs out */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Adds Amount spare rounds to the equipped weapon and refreshes the HUD. Returns false without a weapon in hand or once dead */
	bool AddReserveAmmo(int32 Amount);

	/** Called once by AU_ClaudPortfGameMode when the game ends: stops movement and input, shows the mouse cursor, then calls OnVictory or OnGameOver */
	void HandleGameEnded(bool bVictory);


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for equip input */
	void Equip();

	/** Called for fire input */
	void Fire();

	/** Called for reload input */
	void Reload();

	/** Stops movement and player input, and reports Game Over to the game mode */
	void Die();

	/** Stops the character and removes its input (Move/Look/Jump/Equip/Fire/Reload) */
	void StopMovementAndInput();

	/** Called once when every enemy has died. Implement in the Blueprint to show WBP_Victory */
	UFUNCTION(BlueprintImplementableEvent, Category = Game)
	void OnVictory();

	/** Called once when the player has died. Implement in the Blueprint to show the Game Over widget */
	UFUNCTION(BlueprintImplementableEvent, Category = Game)
	void OnGameOver();

	/** Shows the equipped weapon's ammo on PlayerHUD, or placeholders without a weapon. Called whenever the ammo or weapon changes */
	void UpdateAmmoHUD();

	/** Shows CurrentHealth / MaxHealth on PlayerHUD's health text and bar. Called whenever the health changes */
	void UpdateHealthHUD();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns the weapon currently in pickup range **/
	FORCEINLINE AWeapon* GetOverlappingWeapon() const { return OverlappingWeapon; }
	/** Returns the weapon currently held in hand **/
	FORCEINLINE AWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
	/** Returns the maximum health **/
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	/** Returns the remaining health **/
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	/** Returns true once the player has died **/
	FORCEINLINE bool IsDead() const { return bIsDead; }
};

