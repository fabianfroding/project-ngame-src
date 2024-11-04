// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NDamageFlashComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NGAME_API UNDamageFlashComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FTimerHandle ResetFlashTimerHandle;

protected:
	UPROPERTY(EditDefaultsOnly)
	float FlashDuration = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName EmissiveVectorParameterName = "EmissiveColor";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName EmissiveMultiplierParameterName = "EmissiveMultiplier";

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* FlashMaterial;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor DefaultEmissiveColor;

	UPROPERTY(BlueprintReadWrite)
	float DefaultEmissiveMultiplier = 0.f;

public:	
	UNDamageFlashComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDamaged(float DamageAmount, AActor* DamageSource);
	void OnDamaged_Implementation(float DamageAmount, AActor* DamageSource);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ResetFlashMaterial();
};
