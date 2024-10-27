// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Pawns/Components/NPlayerWeaponsManagerComponent.h"

UNPlayerWeaponsManagerComponent::UNPlayerWeaponsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNPlayerWeaponsManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UNPlayerWeaponsManagerComponent::AddWeapon(UNWeaponPrimaryAsset* WeaponPA)
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
