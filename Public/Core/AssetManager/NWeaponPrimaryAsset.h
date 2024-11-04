// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Core/AssetManager/NPrimaryDataAsset.h"
#include "Weapons/NWeapon.h"

#include "NWeaponPrimaryAsset.generated.h"

UCLASS()
class NGAME_API UNWeaponPrimaryAsset : public UNPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UNWeapon> SoftWeaponClass;

	UPROPERTY(EditDefaultsOnly)
	FWeaponSettings WeaponSettings;
	
};
