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
	//===== End GAS Properties =====//

public:
	ANNPCPawnBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	void OnDeath() { Destroy(); }

protected:
	UFUNCTION()
	void OnAbilitySystemComponentInitialized(UActorComponent* Component, bool bReset);

};
