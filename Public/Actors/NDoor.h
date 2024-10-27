// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NDoor.generated.h"

class UNLevelGenerationPrimaryAsset;;
class UNLevelPrimaryAsset;

UENUM(BlueprintType)
enum class ENDoorState : uint8
{
    E_CLOSED   UMETA(DisplayName = "Closed"),
    E_CLOSIING UMETA(DisplayName = "Closing"),
    E_OPEN UMETA(DisplayName = "Open"),
    E_OPENING UMETA(DisplayName = "Opening"),
    E_READY UMETA(DisplayName = "Ready")
};

UCLASS()
class NGAME_API ANDoor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle CurrentStateTimer;

    UPROPERTY(BlueprintReadWrite)
    ENDoorState DoorState = ENDoorState::E_CLOSED;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UNLevelPrimaryAsset* LevelToLoad;
};
