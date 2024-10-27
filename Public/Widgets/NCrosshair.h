// Copyright HungryHusky Games 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "NCrosshair.generated.h"

class ANWeapon;

UCLASS()
class NGAME_API UNCrosshair : public UUserWidget
{
	GENERATED_BODY()
	
public:
	ANWeapon* OwningWeapon;

};
