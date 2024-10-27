// Copyright HungryHusky Games 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "NPrimaryDataAsset.generated.h"

UCLASS()
class NGAME_API UNPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Type of this item, set in native parent class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType AssetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText AssetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* AssetIcon;

public:
	// Overridden to use saved type
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId(AssetType, GetFName()); }

	UFUNCTION(BlueprintPure)
	virtual FText GetDescription() { return FText(); }
	
};
