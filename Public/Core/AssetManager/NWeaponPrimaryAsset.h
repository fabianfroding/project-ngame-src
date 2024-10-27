// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Core/AssetManager/NPrimaryDataAsset.h"

#include "NWeaponPrimaryAsset.generated.h"

class ANWeapon;

UCLASS()
class NGAME_API UNWeaponPrimaryAsset : public UNPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<ANWeapon> SoftWeaponClass;
	
};
