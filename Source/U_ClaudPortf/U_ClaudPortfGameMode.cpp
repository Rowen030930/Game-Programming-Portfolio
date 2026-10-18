// Copyright Epic Games, Inc. All Rights Reserved.

#include "U_ClaudPortfGameMode.h"
#include "U_ClaudPortfCharacter.h"
#include "UObject/ConstructorHelpers.h"

AU_ClaudPortfGameMode::AU_ClaudPortfGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
