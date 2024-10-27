// Copyright HungryHusky Games 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "NAbilityResourceAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class NGAME_API UNAbilityResourceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData ResourceAmount;
	ATTRIBUTE_ACCESSORS(UNAbilityResourceAttributeSet, ResourceAmount);

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxResourceAmount;
	ATTRIBUTE_ACCESSORS(UNAbilityResourceAttributeSet, MaxResourceAmount);
	
};
