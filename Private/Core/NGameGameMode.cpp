// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/NGameGameMode.h"

#include "Pawns/NGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANGameGameMode::ANGameGameMode() : Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
