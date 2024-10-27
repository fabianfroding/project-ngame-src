// Copyright HungryHusky Games 2024

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/NPawnBaseInterface.h"

#include "NNPCPawnBase.generated.h"

class UAbilitySystemComponent;
class UNDamageFlashComponent;
class UNHealthComponent;

UCLASS()
class NGAME_API ANNPCPawnBase : public APawn, public INPawnBaseInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UNHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	class UNDamageFlashComponent* DamageFlashComponent;

	//===== GAS Properties =====//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const class UNHealthAttributeSet* HealthAttributeSet;
	//===== End GAS Properties =====//

public:
	ANNPCPawnBase();

	UFUNCTION(BlueprintPure)
	UNHealthComponent* GetHealthComponent() const { return HealthComponent; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	void OnDeath() { Destroy(); }
};
