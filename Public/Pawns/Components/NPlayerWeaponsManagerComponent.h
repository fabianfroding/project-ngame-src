// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Core/AssetManager/NWeaponPrimaryAsset.h"
#include "Components/ActorComponent.h"

#include "NPlayerWeaponsManagerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NGAME_API UNPlayerWeaponsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNPlayerWeaponsManagerComponent();

	bool AddWeapon(UNWeaponPrimaryAsset* WeaponPA);
	void SwitchWeapon(const bool AscendingOrder);
	UNWeaponPrimaryAsset* GetActiveWeapon();

protected:
	virtual void BeginPlay() override;
};
