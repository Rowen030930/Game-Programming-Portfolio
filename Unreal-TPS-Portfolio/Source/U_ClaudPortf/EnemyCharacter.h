// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UAnimMontage;
class UWidgetComponent;
struct FBranchingPointNotifyPayload;

UCLASS()
class AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Health the enemy starts with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true", ClampMin = "1.0"))
	float MaxHealth = 100.f;

	/** Remaining health; the enemy dies when this reaches 0 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 0.f;

	/** True once Die() has run; further damage is ignored */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	/** Seconds the ragdoll stays in the level before the actor is removed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float DeathLifeSpan = 5.f;

	/** Bone whose Physics Asset body counts as the head for headshots (PA_Mannequin has a body on SK_Mannequin's "head" bone) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	FName HeadBoneName = TEXT("head");

	/** Name of the Widget Component added in the Blueprint (BP_EnemyCharacter) that shows the health bar */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	FName HealthWidgetComponentName = TEXT("EnemyHealthWidget");

	/** Name of the Progress Bar in that component's widget whose Percent shows CurrentHealth / MaxHealth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	FName HealthBarName = TEXT("PB_Health");

	/** Widget Component named HealthWidgetComponentName, found in BeginPlay; null if the Blueprint has none */
	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> HealthWidgetComponent = nullptr;

	/** Damage applied to the target per melee attack */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float AttackDamage = 10.f;

	/**
	 * The target must be within this center distance for an attack to start. Whether it lands is decided by the kicking foot (KickFootBone).
	 * At the AttackHit notify of AM_Enemy_QuickTimeKick the right foot reaches about 120 in front of the enemy, so it touches
	 * a 42-radius player capsule up to roughly 160-175 away
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float AttackRange = 160.f;

	/** Minimum seconds between two attacks */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "0.1"))
	float AttackInterval = 1.5f;

	/** A swing only starts once the target is within this angle (degrees) of the enemy's facing; until then the enemy turns toward it */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "180.0"))
	float AttackStartAngle = 30.f;

	/** The attack only lands if the target is within this angle (degrees) of the enemy's facing at the moment of impact */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "180.0"))
	float AttackHitAngle = 60.f;

	/** Bone the kick hits with (AM_Enemy_QuickTimeKick kicks with the right foot). The hit shape runs from here to KickTipBone */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	FName KickFootBone = TEXT("foot_r");

	/** Tip of the kicking foot (SK_Mannequin has no toe bones; ball_r is the ball of the foot) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	FName KickTipBone = TEXT("ball_r");

	/** Radius of the capsule swept from KickFootBone to KickTipBone that must overlap the target's collision for the kick to land */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "1.0"))
	float KickHitRadius = 12.f;

	/** Draws the kick hit shape for 2 seconds at every AttackHit notify (green: landed, red: missed) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool bDrawKickHitDebug = false;

	/** Horizontal speed a landed attack pushes a character target away from the enemy with. 0 disables the knockback */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float KnockbackStrength = 400.f;

	/** Upward speed added to the knockback so the target briefly leaves the ground instead of being stopped by ground friction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float KnockbackUpwardSpeed = 150.f;

	/** Actor currently being attacked; null while not attacking */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	AActor* AttackTarget = nullptr;

	/**
	 * Montage played for each attack (must use the DefaultSlot that ABP_Manny's AnimGraph plays).
	 * Damage is applied when its Montage Notify named AttackHitNotifyName fires. Without a montage, damage is applied immediately
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage = nullptr;

	/** Name of the Montage Notify in AttackMontage that marks the moment the attack lands */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	FName AttackHitNotifyName = TEXT("AttackHit");

	FTimerHandle AttackTimerHandle;

	/** World time of the last attack; negative until the first one */
	double LastAttackTime = -1.0;

	/** True between starting an attack montage and its hit notify */
	bool bAttackHitPending = false;

	/** True once the "montage never reached its hit notify" warning has been logged */
	bool bWarnedMissingHitNotify = false;

	/** Movement component rotation settings used while chasing, restored when the attack stops */
	bool bChaseOrientRotationToMovement = true;
	bool bChaseUseControllerDesiredRotation = false;

public:
	AEnemyCharacter();

	/** Reduces CurrentHealth and calls Die() when it runs out */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Returns true if Hit is on this enemy mesh's HeadBoneName physics body */
	bool IsHeadHit(const FHitResult& Hit) const;

	/** Returns true if Target is within AttackRange */
	bool IsInAttackRange(const AActor* Target) const;

	/** Returns true if Target is within MaxAngle degrees of the enemy's facing (ignoring height) */
	bool IsFacing(const AActor* Target, float MaxAngle) const;

	/** Returns true if no Visibility-blocking geometry lies between the enemy and Target */
	bool HasLineOfSightTo(const AActor* Target) const;

	/**
	 * Returns true if the kicking foot (KickFootBone to KickTipBone, KickHitRadius thick) overlaps Target's root collision.
	 * Logs a warning and returns false if the mesh lacks either bone
	 */
	bool IsKickTouching(const AActor* Target) const;

	/** Attacks Target every AttackInterval seconds until StopAttacking() is called */
	void StartAttacking(AActor* Target);

	/** Stops the repeating attack */
	void StopAttacking();

protected:
	virtual void BeginPlay() override;

	/** Stops movement, releases the controller and capsule, and switches the mesh to ragdoll */
	void Die();

	/** Sets the health bar's Percent to CurrentHealth / MaxHealth */
	void UpdateHealthBar();

	/** Turns toward AttackTarget while attacking (true), or restores the chase rotation settings (false) */
	void SetFacingAttackTarget(bool bFace);

	/**
	 * Starts an attack on AttackTarget if it is still alive, in range and in front: plays AttackMontage, or applies damage right away without one.
	 * Schedules the next call itself
	 */
	void PerformAttack();

	/** Applies AttackDamage to AttackTarget if it is still alive, in front, not behind cover and touched by the kicking foot at the moment the attack lands */
	void ApplyAttackDamage();

	/** Applies the pending attack's damage when AttackMontage reaches AttackHitNotifyName */
	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

public:
	/** Returns the maximum health **/
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	/** Returns the remaining health **/
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	/** Returns true once the enemy has died **/
	FORCEINLINE bool IsDead() const { return bIsDead; }
	/** Returns true while an attack target is set **/
	FORCEINLINE bool IsAttacking() const { return AttackTarget != nullptr; }
};
