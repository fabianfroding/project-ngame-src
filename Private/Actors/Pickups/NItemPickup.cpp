// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Actors/Pickups/NItemPickup.h"

ANItemPickup::ANItemPickup()
{
	PickupComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMeshComponent"));
	CreatePickupCollider();
}
