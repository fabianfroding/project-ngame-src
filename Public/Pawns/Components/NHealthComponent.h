// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NGAME_API UNHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FTimerHandle InvulnerabilityFramesTimer;
	TMap<FString, bool> InvulnerabilityMap;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const class UNHealthAttributeSet* HealthAttributeSet;

	UPROPERTY(EditDefaultsOnly)
	float InvulnerabilityFramesDuration = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> DamagedSounds;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;

public:	
	UNHealthComponent();

	UFUNCTION(BlueprintPure)
	static UNHealthComponent* FindHealthComponent(const AActor* Actor) 
	{ return (Actor ? Actor->FindComponentByClass<UNHealthComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable)
	void InitializeWithAbilitySystem(UAbilitySystemComponent* InASC);

	bool IsInvulnerable() const;
	void SetInvulnerability(const FString InvulnerabilityKey, const bool bNewInvulnerability);
	float GetInvulnerabilityFramesDuration() const { return InvulnerabilityFramesDuration; }
	void ResetInvulnerabilityFrames() { SetInvulnerability("InvulnerabilityFrames", false); }

	bool IsAlive() const;
	bool IsAtFullHealth() const;

	void PlayDamagedSound();

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable)
	static void KillActor(AActor* ActorToKill);

	UFUNCTION(BlueprintCallable)
	static void ApplyHealthDamage(AActor* DamagedActor, AController* Instigator, AActor* DamageCauser, float Damage);
};
