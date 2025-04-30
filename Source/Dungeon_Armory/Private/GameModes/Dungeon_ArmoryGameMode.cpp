// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/Dungeon_ArmoryGameMode.h"
#include "Characters/Dungeon_ArmoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeon_ArmoryGameMode::ADungeon_ArmoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Player/Mannequin/Blueprints/BP_Manny"));
	if (PlayerPawnBPClass.Class != NULL)
	{

		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
