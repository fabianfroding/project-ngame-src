// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Pawns/Components/NHealthComponent.h"

#include "GameplayAbilitySystem/AttributeSets/NHealthAttributeSet.h"
#include "GameplayEffect.h"
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

void UNHealthComponent::PlayOnDamagedFeedback()
{
	if (ChanceToPlayDamagedSounds <= 0.f)
		return;

	if (DamagedSounds.IsEmpty())
		return;

	const AActor* OwningActor = GetOwner();
	if (!IsValid(OwningActor))
		return;

	const int32 RandomizedIndex = FMath::RandRange(0, DamagedSounds.Num() - 1);
	if (!DamagedSounds.IsValidIndex(RandomizedIndex))
		return;

	USoundBase* RandomizedSound = DamagedSounds[RandomizedIndex];

	UGameplayStatics::PlaySoundAtLocation(this, RandomizedSound, OwningActor->GetActorLocation());
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

void UNHealthComponent::TakeDamage(FGameplayEffectSpecHandle GameplayEffectSpecHandle, AActor* DamageSource)
{
	if (IsInvulnerable())
		return;

	const float HealthBefore = HealthAttributeSet->GetHealth();

	if (GameplayEffectSpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

		float TrueDamageAmount = HealthBefore - FMath::Clamp(HealthAttributeSet->GetHealth(), 0.f, HealthAttributeSet->GetMaxHealth());
		if (TrueDamageAmount > 0.f)
		{
			PlayOnDamagedFeedback();
			OnDamaged.Broadcast(TrueDamageAmount, DamageSource);
		}

		if (InvulnerabilityFramesDuration > 0.f)
		{
			UWorld* World = GetWorld();
			if (IsValid(World))
			{
				SetInvulnerability(InvulnerabilityFramesKey, true);
				World->GetTimerManager().SetTimer(InvulnerabilityFramesTimer, this, &UNHealthComponent::ResetInvulnerabilityFrames, InvulnerabilityFramesDuration, false);
			}
		}

		HandleDeath();
	}
}

void UNHealthComponent::HandleDeath()
{
	if (!IsAlive())
		return;

	if (HealthAttributeSet->GetHealth() <= 0.f)
		OnDie.Broadcast();
}
