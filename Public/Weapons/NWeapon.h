// Copyright HungryHusky Games 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Widgets/NCrosshair.h"

#include "NWeapon.generated.h"

UCLASS()
class NGAME_API ANWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = Runtime)
	UNCrosshair* Crosshair;

public:
	UNCrosshair* GetCrosshair() const { return Crosshair; }
	void SetCrosshair(UNCrosshair* InCrossHair);

	void ShowWeapon(const bool bShow);

};
