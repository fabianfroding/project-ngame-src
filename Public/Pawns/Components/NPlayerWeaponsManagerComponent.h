// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NPlayerWeaponsManagerComponent.generated.h"

class UNWeapon;
class UNWeaponPrimaryAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchedToWeapon, UNWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddedWeapon, UNWeaponPrimaryAsset*, WeaponPrimaryAsset, int32, SlotIndex);

UENUM(BlueprintType)
enum class ENWeaponSwitchState : uint8
{
	E_Up				UMETA(DisplayName = "Up"),
	E_Down				UMETA(DisplayName = "Down"),
	E_PutDownPrevious	UMETA(DisplayName = "PutDownPrevious"),
	E_PutUpNew			UMETA(DisplayName = "PutUpNew")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NGAME_API UNPlayerWeaponsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<UNWeaponPrimaryAsset*> StartingWeapons;

	UPROPERTY(EditDefaultsOnly)
	TArray<UNWeaponPrimaryAsset*> WeaponSlots;

	// Collission channel to set FPS weapon actors to.
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> FPSWeaponCollisionChannel;

	ENWeaponSwitchState WeaponSwitchState;

public:
	int32 ActiveWeaponIndex = -1;

	UPROPERTY(BlueprintAssignable)
	FOnSwitchedToWeapon OnSwitchedToWeapon;

	UPROPERTY(BlueprintAssignable)
	FOnAddedWeapon OnAddedWeapon;

public:
	UNPlayerWeaponsManagerComponent();

	bool AddWeapon(UNWeaponPrimaryAsset* WeaponPA);

	bool HasWeapon(UNWeaponPrimaryAsset* WeaponPA);

	void SwitchWeapon(const bool AscendingOrder);

	UNWeaponPrimaryAsset* GetActiveWeapon();

	UFUNCTION()
	void OnWeaponSwitched(UNWeapon* NewWeapon);

protected:
	virtual void BeginPlay() override;

};
