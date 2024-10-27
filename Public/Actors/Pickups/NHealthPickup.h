// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/NPickupBase.h"

#include "NHealthPickup.generated.h"

UCLASS()
class NGAME_API ANHealthPickup : public ANPickupBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Health")
	float HealAmount = 50.f;

	void OnPickedUp_Implementation(APlayerController* PlayerController) override;
};
