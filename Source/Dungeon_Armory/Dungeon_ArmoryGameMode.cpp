// Copyright Epic Games, Inc. All Rights Reserved.

#include "Dungeon_ArmoryGameMode.h"
#include "Dungeon_ArmoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeon_ArmoryGameMode::ADungeon_ArmoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
