// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "NHealthComponent.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamaged, float, DamageAmount, AActor*, DamageSource);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NGAME_API UNHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	FTimerHandle InvulnerabilityFramesTimer;
	TMap<FString, bool> InvulnerabilityMap;

	const FString InvulnerabilityFramesKey = "InvulnerabilityFrames";

protected:
	//===== GAS Properties =====//
	UPROPERTY(BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const class UNHealthAttributeSet* HealthAttributeSet;
	//===== End GAS Properties =====//

	UPROPERTY(EditDefaultsOnly)
	float InvulnerabilityFramesDuration = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "NHealthComponent|Audio")
	float ChanceToPlayDamagedSounds = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "NHealthComponent|Audio")
	TArray<USoundBase*> DamagedSounds;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDie OnDie;

	UPROPERTY(BlueprintAssignable)
	FOnDamaged OnDamaged;

public:	
	UNHealthComponent();

	UFUNCTION(BlueprintPure)
	static UNHealthComponent* FindHealthComponent(const AActor* Actor) 
	{ return (Actor ? Actor->FindComponentByClass<UNHealthComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable)
	void InitializeWithAbilitySystem(UAbilitySystemComponent* InASC);

	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }

	bool IsInvulnerable() const;
	void SetInvulnerability(const FString InvulnerabilityKey, const bool bNewInvulnerability);
	float GetInvulnerabilityFramesDuration() const { return InvulnerabilityFramesDuration; }
	void ResetInvulnerabilityFrames() { SetInvulnerability(InvulnerabilityFramesKey, false); }

	bool IsAlive() const;
	bool IsAtFullHealth() const;

	void PlayOnDamagedFeedback();

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable)
	static void KillActor(AActor* ActorToKill);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource);

	void HandleDeath();

};
