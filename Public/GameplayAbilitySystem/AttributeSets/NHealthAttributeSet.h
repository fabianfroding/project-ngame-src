// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "NHealthAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class NGAME_API UNHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

private:
	TMap<FString, bool> InvulnerabilityMap;

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UNHealthAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UNHealthAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData DamagedInvulnerabilityDuration;
	ATTRIBUTE_ACCESSORS(UNHealthAttributeSet, DamagedInvulnerabilityDuration);

public:
	UFUNCTION(BlueprintCallable)
	void TakeDamage(AActor* DamagedActor, AController* Instigator, AActor* DamageCauser, float DamageAmount);

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintPure)
	bool IsAlive() const { return Health.GetCurrentValue() > 0.f; }

	bool IsAtFullHealth() const { return Health.GetCurrentValue() < MaxHealth.GetCurrentValue(); }

	UFUNCTION(BlueprintPure)
	bool IsInvulnerable();

	UFUNCTION(BlueprintCallable)
	void SetIsInvulnerable(const FString InvulnerabilityIdentifier, const bool NewInvulnerability);

	UFUNCTION(BlueprintCallable)
	void Kill();

	void HandleDeath();
	
};
