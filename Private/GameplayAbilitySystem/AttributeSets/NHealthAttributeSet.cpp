// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "GameplayAbilitySystem/AttributeSets/NHealthAttributeSet.h"

void UNHealthAttributeSet::TakeDamage(AActor* DamagedActor, AController* Instigator, AActor* DamageCauser, float DamageAmount)
{
	if (IsInvulnerable() || !IsAlive())
		return;

	const float HealthBefore = Health.GetCurrentValue();
	Health.SetCurrentValue(HealthBefore - DamageAmount);
	Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, Health.GetCurrentValue()));

	float TrueDamageAmount = HealthBefore - Health.GetCurrentValue();
	if (TrueDamageAmount > 0.f)
	{
		// TODO: Broadcast potential take damage delegate.
	}

	HandleDeath();

	if (!IsAlive())
		return;

	//PlayDamagedSound();
	if (DamagedInvulnerabilityDuration.GetCurrentValue() > 0.f)
		SetIsInvulnerable("DamagedInvulnerability", true);

	/*if (IsValid(DamageCauser))
	{
		// TODO: This should be more abstracted.
		if (ANGameCharacter* NGameCharacter = Cast<ANGameCharacter>(DamageCauser))
		{
			FNDamageEventData DamageEventData;
			DamageEventData.DamageAmount = Damage;
			DamageEventData.DamagedActor = DamagedActor;
			NGameCharacter->OnPlayerDealtDamage.Broadcast(DamageEventData);
		}
	}*/
}

void UNHealthAttributeSet::Heal(float HealAmount)
{
	const float HealthBefore = Health.GetCurrentValue();
	Health.SetCurrentValue(HealthBefore + HealAmount);
	Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));

	const float TrueHealAmount = Health.GetCurrentValue() - HealthBefore;
	if (TrueHealAmount > 0.f)
	{
		// TODO: Broadcast delegate if needed.
	}
}

bool UNHealthAttributeSet::IsInvulnerable()
{
	for (TPair<FString, bool>& Invulnerability : InvulnerabilityMap)
	{
		if (Invulnerability.Value == true)
			return true;
	}
	return false;
}

void UNHealthAttributeSet::SetIsInvulnerable(const FString InvulnerabilityIdentifier, const bool NewInvulnerability)
{
	InvulnerabilityMap.Add(InvulnerabilityIdentifier, NewInvulnerability);
	//if (InvulnerabilityDuration > 0.f)
		//GetWorld()->GetTimerManager().SetTimer(InvulnerabilityTimer, this, &UNHealthComponent::ResetInvulnerability, InvulnerabilityDuration, false);
}

void UNHealthAttributeSet::Kill()
{
	Health.SetCurrentValue(0.f);
	// TODO: Broadcast >Damaged< delegate if needed.
	HandleDeath();
}

void UNHealthAttributeSet::HandleDeath()
{
	if (!IsAlive())
		return;

	if (Health.GetCurrentValue() <= 0.f)
	{
		// TODO: Broadcast OnDie delegate if needed.
	}
}
