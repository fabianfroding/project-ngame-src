// Copyright HungryHusky Games 2024

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
	FTimerHandle InvulnerabilityTimer;
	bool bIsInvulnerable = false; // TODO: Make to TMap for multiple invulnerability sources.

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float CurrentHealth = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float InvulnerabilityDuration = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> DamagedSounds;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 1.f;

	UPROPERTY(BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;

public:	
	UNHealthComponent();
	virtual void BeginPlay() override;

	bool GetIsInvulnerable() const { return bIsInvulnerable; }
	void SetIsInvulnerable(bool bNewInvulnerable);

	float GetInvulnerabilityDuration() const { return InvulnerabilityDuration; }

	void ResetInvulnerability() { bIsInvulnerable = false; }

	bool IsAlive() const { return CurrentHealth > 0.f; }

	bool IsAtFullHealth() const { return CurrentHealth < MaxHealth; }

	void PlayDamagedSound();

	UFUNCTION(BlueprintCallable)
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable)
	static void KillActor(AActor* ActorToKill);

	UFUNCTION(BlueprintCallable)
	static UNHealthComponent* GetHealthComponent(const AActor* OwningActor);

	UFUNCTION(BlueprintCallable)
	static void ApplyHealthDamage(AActor* DamagedActor, AController* Instigator, AActor* DamageCauser, float Damage);
};
