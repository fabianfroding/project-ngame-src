// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Core/AssetManager/NPrimaryDataAsset.h"

#include "NLevelPrimaryAsset.generated.h"

UCLASS()
class NGAME_API UNLevelPrimaryAsset : public UNPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly ,BlueprintReadOnly)
	FName LevelName;
	
};
