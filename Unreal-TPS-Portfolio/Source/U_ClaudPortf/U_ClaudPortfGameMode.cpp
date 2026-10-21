// Copyright Epic Games, Inc. All Rights Reserved.

#include "U_ClaudPortfGameMode.h"
#include "U_ClaudPortfCharacter.h"
#include "EnemyCharacter.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameResult, Log, All);

AU_ClaudPortfGameMode::AU_ClaudPortfGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AU_ClaudPortfGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Only enemies in the level at this point count. Enemies spawned later (or streamed in by World Partition later) don't affect Victory
	for (TActorIterator<AEnemyCharacter> It(GetWorld()); It; ++It)
	{
		AEnemyCharacter* Enemy = *It;
		if (!IsValid(Enemy) || Enemy->IsDead())
		{
			continue;
		}

		AliveEnemies.Add(Enemy);
		Enemy->OnDestroyed.AddDynamic(this, &AU_ClaudPortfGameMode::OnEnemyDestroyed);
	}
	TotalEnemyCount = AliveEnemies.Num();
	AliveEnemyCount = TotalEnemyCount;

	// A level without enemies has nothing to win, so it never ends in Victory (only the player's death ends it)
	if (TotalEnemyCount == 0)
	{
		UE_LOG(LogGameResult, Warning, TEXT("'%s' No AEnemyCharacter in the level at start, so Victory can't happen"), *GetNameSafe(this));
		return;
	}

	UE_LOG(LogGameResult, Log, TEXT("'%s' Enemies to defeat: %d"), *GetNameSafe(this), TotalEnemyCount);
}

void AU_ClaudPortfGameMode::NotifyEnemyKilled(AEnemyCharacter* Enemy)
{
	RemoveAliveEnemy(Enemy);
}

void AU_ClaudPortfGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	// Normally the enemy already left the count when it died, and its ragdoll is only being cleaned up here
	RemoveAliveEnemy(Cast<AEnemyCharacter>(DestroyedActor));
}

void AU_ClaudPortfGameMode::RemoveAliveEnemy(AEnemyCharacter* Enemy)
{
	// Unknown (uncounted or already removed) enemies change nothing, so each enemy lowers the count exactly once
	if (Enemy == nullptr || AliveEnemies.Remove(Enemy) == 0)
	{
		return;
	}

	AliveEnemyCount = AliveEnemies.Num();
	UE_LOG(LogGameResult, Log, TEXT("'%s' '%s' defeated. Enemies left: %d / %d"), *GetNameSafe(this), *GetNameSafe(Enemy), AliveEnemyCount, TotalEnemyCount);

	if (AliveEnemyCount == 0)
	{
		EndGame(EGameResult::Victory);
	}
}

void AU_ClaudPortfGameMode::NotifyPlayerDied()
{
	EndGame(EGameResult::GameOver);
}

void AU_ClaudPortfGameMode::EndGame(EGameResult Result)
{
	// The first result wins: a player killed after Victory (or the last enemy killed after Game Over) changes nothing
	if (IsGameEnded() || Result == EGameResult::None)
	{
		return;
	}
	GameResult = Result;

	UE_LOG(LogGameResult, Log, TEXT("'%s' Game ended: %s"), *GetNameSafe(this), Result == EGameResult::Victory ? TEXT("Victory") : TEXT("Game Over"));

	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AU_ClaudPortfCharacter* Player = PlayerController ? Cast<AU_ClaudPortfCharacter>(PlayerController->GetPawn()) : nullptr;
	if (Player == nullptr)
	{
		UE_LOG(LogGameResult, Warning, TEXT("'%s' No AU_ClaudPortfCharacter is possessed by the player, so no result screen is shown"), *GetNameSafe(this));
		return;
	}

	Player->HandleGameEnded(Result == EGameResult::Victory);
}

void AU_ClaudPortfGameMode::RestartCurrentLevel()
{
	// The viewport keeps the UI input mode across a level load, so hand the mouse back to the game first
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
}

void AU_ClaudPortfGameMode::QuitCurrentGame()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
