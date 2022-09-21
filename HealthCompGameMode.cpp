// Copyright Epic Games, Inc. All Rights Reserved.

#include "HealthCompGameMode.h"
#include "HealthCompCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHealthCompGameMode::AHealthCompGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
