// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Actors/Pickups/NHealthPickup.h"

#include "Core/NGamePlayerController.h"
#include "Pawns/Components/NHealthComponent.h"

void ANHealthPickup::OnPickedUp_Implementation(APlayerController* PlayerController)
{
	ANGamePlayerController* PlayerCharacter = Cast<ANGamePlayerController>(PlayerController);
	if (PlayerCharacter)
	{
		UNHealthComponent* PlayerHealthComp = PlayerCharacter->FindComponentByClass<UNHealthComponent>();
		if (PlayerHealthComp && !PlayerHealthComp->IsAtFullHealth())
		{
			PlayerHealthComp->Heal(HealAmount);
			PlayPickupFeedback();
			Destroy();
		}
	}
}
