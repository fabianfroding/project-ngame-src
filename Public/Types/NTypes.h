// Copyright HungryHusky Games 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NTypes.generated.h"

UCLASS()
class NGAME_API ANTypes : public AActor { GENERATED_BODY() };

USTRUCT(BlueprintType)
struct FNDamageEventData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	float DamageAmount;

	UPROPERTY(BlueprintReadWrite)
	AActor* DamagedActor;
};
