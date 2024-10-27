// Copyright Epic Games, Inc. All Rights Reserved.


#include "Core/NGamePlayerController.h"
#include "EnhancedInputSubsystems.h"

void ANGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}