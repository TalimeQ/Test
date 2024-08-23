// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestParadarkGameMode.h"
#include "TestParadarkCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestParadarkGameMode::ATestParadarkGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
