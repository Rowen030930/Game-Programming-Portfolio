// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "U_ClaudPortfGameMode.generated.h"

class AEnemyCharacter;

/** How the current play session ended */
UENUM(BlueprintType)
enum class EGameResult : uint8
{
	/** Still playing */
	None,
	/** Every enemy counted at BeginPlay has died */
	Victory,
	/** The player died */
	GameOver
};

UCLASS(minimalapi)
class AU_ClaudPortfGameMode : public AGameModeBase
{
	GENERATED_BODY()

	/** Enemies alive in the level when play started */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = "true"))
	int32 TotalEnemyCount = 0;

	/** Counted enemies that haven't died yet; Victory when this reaches 0 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = "true"))
	int32 AliveEnemyCount = 0;

	/** None while playing; set once to Victory or GameOver and never changed afterwards */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = "true"))
	EGameResult GameResult = EGameResult::None;

	/** Enemies counted in AliveEnemyCount that haven't died yet. Each is removed once, so a second death or destruction report changes nothing */
	TSet<TObjectKey<AEnemyCharacter>> AliveEnemies;

public:
	AU_ClaudPortfGameMode();

	/** Called by AEnemyCharacter::Die(). Lowers AliveEnemyCount once per counted enemy and ends the game with Victory at 0 */
	void NotifyEnemyKilled(AEnemyCharacter* Enemy);

	/** Called by AU_ClaudPortfCharacter::Die(). Ends the game with GameOver unless it already ended */
	void NotifyPlayerDied();

	/** Reloads the current level. Call it from the Victory / Game Over widget's retry button */
	UFUNCTION(BlueprintCallable, Category = Game)
	void RestartCurrentLevel();

	/** Quits the game (ends the session in PIE). Call it from the Victory / Game Over widget's quit button */
	UFUNCTION(BlueprintCallable, Category = Game)
	void QuitCurrentGame();

protected:
	/** Counts the enemies placed in the level */
	virtual void BeginPlay() override;

	/** Sets GameResult and tells the player character, only for the first result */
	void EndGame(EGameResult Result);

	/** Removes an enemy destroyed without dying (e.g. by the kill Z) from the count. Does nothing for one already removed by its death */
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);

	/** Removes Enemy from AliveEnemies and ends the game with Victory when none are left */
	void RemoveAliveEnemy(AEnemyCharacter* Enemy);

public:
	/** Returns true once Victory or GameOver has happened **/
	FORCEINLINE bool IsGameEnded() const { return GameResult != EGameResult::None; }
};
