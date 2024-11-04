// Copyright HungryHusky Games 2024

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "NDashAttributeSet.generated.h"


// https://dev.epicgames.com/community/learning/tutorials/zrEb/unreal-engine-how-to-create-attribute-sets-using-unreal-gameplay-ability-system 
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 *
 */
UCLASS()
class NGAME_API UNDashAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayAttributeData AvailableDashes = 2.0f;
	ATTRIBUTE_ACCESSORS(UNDashAttributeSet, AvailableDashes)
	
	UPROPERTY()
	FGameplayAttributeData MaxAvailableDashes = 2.0f;
	ATTRIBUTE_ACCESSORS(UNDashAttributeSet, MaxAvailableDashes)

	UPROPERTY()
	FGameplayAttributeData Duration = 0.2f;
	ATTRIBUTE_ACCESSORS(UNDashAttributeSet, Duration)





};
