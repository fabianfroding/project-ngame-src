// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/NPickupBase.h"

#include "NWeaponPickup.generated.h"

class UNWeaponPrimaryAsset;

UCLASS()
class NGAME_API ANWeaponPickup : public ANPickupBase
{
	GENERATED_BODY()

public:
	ANWeaponPickup();

protected:

	// The weapon that will be added to the player on pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNWeaponPrimaryAsset* WeaponPA;

	virtual void BeginPlay() override;

	virtual void OnPickedUp_Implementation(APlayerController* PlayerController) override;

private:
	void SetChildrenLayersToDefault(); // Set all children layers to default (to prevent seeing weapons through meshes)
	
};
