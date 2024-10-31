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

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UNHealthAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UNHealthAttributeSet, MaxHealth);
	
};
