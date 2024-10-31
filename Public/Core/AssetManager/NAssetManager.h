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

	UFUNCTION(BlueprintPure)
	static UObject* LoadObjectFromSoftObjectPtr(TSoftObjectPtr<UObject> SoftObjectPtr);

	UFUNCTION(BlueprintPure)
	static UClass* LoadClassFromSoftClassPtr(TSoftClassPtr<UObject> SoftClassPtr);
};
