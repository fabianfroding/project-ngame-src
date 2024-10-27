// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Pawns/Components/NPlayerWeaponsManagerComponent.h"

#include "Core/AssetManager/NAssetmanager.h"
#include "Core/AssetManager/NWeaponPrimaryAsset.h"
#include "Weapons/NWeapon.h"

UNPlayerWeaponsManagerComponent::UNPlayerWeaponsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FPSWeaponCollisionChannel = static_cast<TEnumAsByte<ECollisionChannel>>(ECC_GameTraceChannel1);
}

void UNPlayerWeaponsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	ActiveWeaponIndex = -1;
	WeaponSwitchState = ENWeaponSwitchState::E_Down;

	//SetFov(DefaultFov);

	this->OnSwitchedToWeapon.AddUniqueDynamic(this, &UNPlayerWeaponsManagerComponent::OnWeaponSwitched);

	// Add starting weapons.
	for (UNWeaponPrimaryAsset* WeaponPA : StartingWeapons)
	{
		AddWeapon(WeaponPA);
	}

	SwitchWeapon(true);
}

bool UNPlayerWeaponsManagerComponent::AddWeapon(UNWeaponPrimaryAsset* WeaponPA)
{
	if (HasWeapon(WeaponPA))
		return false;

	// Search weapon slots for the first free one, assign the weapon to it, and return true if we found one. Return false otherwise
	for (int32 i = 0; i < WeaponSlots.Num(); i++)
	{
		// only add the weapon if the slot is free
		if (WeaponSlots[i] == nullptr)
		{
			UWorld* const World = GetWorld();
			TSubclassOf<ANWeapon> WeaponClass = UNAssetManager::LoadClassFromSoftClassPtr(WeaponPA->SoftWeaponClass);

			if (World != nullptr && WeaponClass != nullptr)
			{
				// Spawn weapon object as child of the weapon socket.
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
				ANWeapon* SpawnedWeapon = World->SpawnActor<ANWeapon>(WeaponClass, SpawnParams); // TODO: Spawn at transform "WeaponParentSocket".
				SpawnedWeapon->SetActorRelativeLocation(FVector::ZeroVector);
				SpawnedWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);

				// Set owner to this component so the weapon can alter projectile/damage logic accordingly.
				SpawnedWeapon->SetOwner(this->GetOwner());
				SpawnedWeapon->ShowWeapon(false);

				// Assign the first person collision channel to the weapon.
				TArray<USceneComponent*> ChildComponents;
				SpawnedWeapon->GetComponents<USceneComponent>(ChildComponents);
				for (USceneComponent* Component : ChildComponents)
				{
					if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component))
					{
						PrimitiveComponent->SetCollisionObjectType(FPSWeaponCollisionChannel);
						PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
					}
				}

				WeaponSlots[i] = WeaponPA;

				if (OnAddedWeapon.IsBound())
					OnAddedWeapon.Broadcast(WeaponPA, i);

				return true;
			}
		}
	}

	// Auto-switch to weapon if player has no weapon.
	if (GetActiveWeapon() == nullptr)
		SwitchWeapon(true);

	return false;
}

bool UNPlayerWeaponsManagerComponent::HasWeapon(UNWeaponPrimaryAsset* WeaponPA)
{
	return false;
}

void UNPlayerWeaponsManagerComponent::SwitchWeapon(const bool AscendingOrder)
{

}

UNWeaponPrimaryAsset* UNPlayerWeaponsManagerComponent::GetActiveWeapon()
{
	return nullptr;
}

void UNPlayerWeaponsManagerComponent::OnWeaponSwitched(ANWeapon* NewWeapon)
{
	if (NewWeapon != nullptr)
		NewWeapon->ShowWeapon(true);
}
