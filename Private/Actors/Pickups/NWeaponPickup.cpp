// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Actors/Pickups/NWeaponPickup.h"

#include "Core/AssetManager/NWeaponPrimaryAsset.h"
#include "Pawns/NGameCharacter.h"
#include "Pawns/Components/NPlayerWeaponsManagerComponent.h"

ANWeaponPickup::ANWeaponPickup()
{
	PickupComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponPickupMeshComponent"));
	CreatePickupCollider();
}

void ANWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	//SetChildrenLayersToDefault();
}

void ANWeaponPickup::OnPickedUp_Implementation(APlayerController* PlayerController)
{
	UE_LOG(LogTemp, Display, TEXT("ANWeaponPickup::OnPickedUp_Implementation: 1"));
	if (!IsValid(PlayerController))
		return;

	UE_LOG(LogTemp, Display, TEXT("ANWeaponPickup::OnPickedUp_Implementation: 2"));
	ANGameCharacter* NGameCharacter = Cast<ANGameCharacter>(PlayerController->GetPawn());
	if (!IsValid(NGameCharacter))
		return;
	
	UE_LOG(LogTemp, Display, TEXT("ANWeaponPickup::OnPickedUp_Implementation: 3"));
	UNPlayerWeaponsManagerComponent* NPlayerWeaponsManagerComponent = NGameCharacter->FindComponentByClass<UNPlayerWeaponsManagerComponent>();
	if (!IsValid(NPlayerWeaponsManagerComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ANWeaponPickup::OnPickedUp_Implementation: Could not find player weapons manager component!"));
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("ANWeaponPickup::OnPickedUp_Implementation: 4"));
	// Add the weapon and switch if no active weapon
	if (NPlayerWeaponsManagerComponent->AddWeapon(WeaponPA))
	{
		UE_LOG(LogTemp, Display, TEXT("ANWeaponPickup::OnPickedUp_Implementation: 5"));
		if (NPlayerWeaponsManagerComponent->GetActiveWeapon() == nullptr)
			NPlayerWeaponsManagerComponent->SwitchWeapon(true);

		PlayPickupFeedback();
		Destroy();
	}
}

void ANWeaponPickup::SetChildrenLayersToDefault()
{
	TArray<USceneComponent*> ChildComponents;
	GetComponents<USceneComponent>(ChildComponents);
	for (USceneComponent* Child : ChildComponents)
	{
		if (Child != GetRootComponent())
		{
			UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Child);
			if (Primitive)
				Primitive->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		}
	}
}
