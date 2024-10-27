// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NLevelManager.generated.h"

class UNLevelPrimaryAsset;

UCLASS()
class NGAME_API ANLevelManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UNLevelPrimaryAsset* CurrentLevel;
	
public:
	ANLevelManager();

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static ANLevelManager* GetLevelManager(const UObject* WorldContextObject);

};
