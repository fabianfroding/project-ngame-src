// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "NAssetManager.generated.h"

UCLASS()
class NGAME_API UNAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static UNAssetManager* GetAssetManager();

	// Tries to get preloaded object. If it fails, it will be loaded syncronously and may cause hitching.
	UFUNCTION(BlueprintPure)
	static UObject* LoadObjectFromSoftObjectPtr(TSoftObjectPtr<UObject> SoftObjectPtr);

	// Tries to get preloaded class. If it fails, it will be loaded syncronously and may cause hitching.
	UFUNCTION(BlueprintPure)
	static UClass* LoadClassFromSoftClassPtr(TSoftClassPtr<UObject> SoftClassPtr);
};
