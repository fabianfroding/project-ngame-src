// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Pawns/Components/NHealthComponent.h"

#include "GameplayAbilitySystem/AttributeSets/NHealthAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/NGameCharacter.h"
#include "Pawns/NNPCPawnBase.h"
#include "Types/NTypes.h"

UNHealthComponent::UNHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNHealthComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UNHealthComponent::InitializeWithAbilitySystem: Health component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("UNHealthComponent::InitializeWithAbilitySystem: Cannot initialize health component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	HealthAttributeSet = AbilitySystemComponent->GetSet<UNHealthAttributeSet>();
	if (!HealthAttributeSet)
	{
		UE_LOG(LogTemp, Error, TEXT("UNHealthComponent::InitializeWithAbilitySystem: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}
}

bool UNHealthComponent::IsInvulnerable() const
{
	if (InvulnerabilityMap.IsEmpty())
		return false;

	for (TPair<FString, bool> Invulnerability : InvulnerabilityMap)
	{
		if (Invulnerability.Value == true)
			return true;
	}

	return false;
}

void UNHealthComponent::SetInvulnerability(const FString InvulnerabilityKey, const bool bNewInvulnerability)
{
	if (bNewInvulnerability)
		InvulnerabilityMap.Add(InvulnerabilityKey, bNewInvulnerability);
	else
		InvulnerabilityMap.Remove(InvulnerabilityKey);
}

bool UNHealthComponent::IsAlive() const
{
	return HealthAttributeSet->GetHealth() > 0.f;
}

bool UNHealthComponent::IsAtFullHealth() const
{
	return HealthAttributeSet->GetHealth() >= HealthAttributeSet->GetMaxHealth();
}

void UNHealthComponent::PlayDamagedSound()
{
	if (IsValid(GetOwner()) && !DamagedSounds.IsEmpty())
		UGameplayStatics::PlaySoundAtLocation(this, DamagedSounds[FMath::RandRange(0, DamagedSounds.Num() - 1)], GetOwner()->GetActorLocation());
}

void UNHealthComponent::Heal(float HealAmount)
{
	const float HealthBefore = HealthAttributeSet->GetHealth();
	/*CurrentHealth += HealAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, HealthAttributeSet->GetMaxHealth());

	const float TrueHealAmount = HealthAttributeSet->GetHealth() - HealthBefore;
	if (TrueHealAmount > 0.f)
	{
		// TODO: Invoke delegate if needed.
	}*/
}

void UNHealthComponent::KillActor(AActor* ActorToKill)
{
	if (IsValid(ActorToKill))
	{
		if (ANNPCPawnBase* NNPCPawnBase = Cast<ANNPCPawnBase>(ActorToKill))
		{
			NNPCPawnBase->OnDeath();
			return;
		}
		if (ANGameCharacter* NGameCharacter = Cast<ANGameCharacter>(ActorToKill))
		{
			NGameCharacter->OnDeath();
		}
	}
}

void UNHealthComponent::ApplyHealthDamage(AActor* DamagedActor, AController* Instigator, AActor* DamageCauser, float Damage)
{
	UNHealthComponent* HealthComp = FindHealthComponent(DamagedActor);
	if (IsValid(HealthComp))
	{
		if (HealthComp->IsInvulnerable() || !HealthComp->IsAlive())
			return;

		//HealthComp->CurrentHealth = FMath::Max(HealthComp->CurrentHealth - Damage, 0.f);
		HealthComp->OnDamageTaken.Broadcast();
		HealthComp->PlayDamagedSound();

		if (HealthComp->HealthAttributeSet->GetHealth() <= 0.f)
		{
			UNHealthComponent::KillActor(DamagedActor);
			return;
		}

		if (HealthComp->GetInvulnerabilityFramesDuration() > 0.f)
		{
			HealthComp->SetInvulnerability("InvulnerabilityFrames", true);
			HealthComp->GetWorld()->GetTimerManager().SetTimer(
				HealthComp->InvulnerabilityFramesTimer, 
				HealthComp, 
				&UNHealthComponent::ResetInvulnerabilityFrames, 
				HealthComp->InvulnerabilityFramesDuration, false);
		}

		if (IsValid(DamageCauser))
		{
			// TODO: This should be more abstracted.
			if (ANGameCharacter* NGameCharacter = Cast<ANGameCharacter>(DamageCauser))
			{
				FNDamageEventData DamageEventData;
				DamageEventData.DamageAmount = Damage;
				DamageEventData.DamagedActor = DamagedActor;
				NGameCharacter->OnPlayerDealtDamage.Broadcast(DamageEventData);
			}
		}
	}
}
