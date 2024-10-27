// Copyright HungryHusky Games 2024

#include "Pawns/Components/NHealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Pawns/NGameCharacter.h"
#include "Pawns/NNPCPawnBase.h"
#include "Types/NTypes.h"

UNHealthComponent::UNHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UNHealthComponent::SetIsInvulnerable(bool bNewInvulnerable)
{
	bIsInvulnerable = bNewInvulnerable;
	if (InvulnerabilityDuration > 0.f)
		GetWorld()->GetTimerManager().SetTimer(InvulnerabilityTimer, this, &UNHealthComponent::ResetInvulnerability, InvulnerabilityDuration, false);
}

void UNHealthComponent::PlayDamagedSound()
{
	if (IsValid(GetOwner()) && !DamagedSounds.IsEmpty())
		UGameplayStatics::PlaySoundAtLocation(this, DamagedSounds[FMath::RandRange(0, DamagedSounds.Num() - 1)], GetOwner()->GetActorLocation());
}

void UNHealthComponent::Heal(float HealAmount)
{
	const float HealthBefore = CurrentHealth;
	CurrentHealth += HealAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);

	const float TrueHealAmount = CurrentHealth - HealthBefore;
	if (TrueHealAmount > 0.f)
	{
		// TODO: Invoke delegate if needed.
	}
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

UNHealthComponent* UNHealthComponent::GetHealthComponent(const AActor* OwningActor)
{
	if (!IsValid(OwningActor))
		return nullptr;
	return OwningActor->FindComponentByClass<UNHealthComponent>();
}

void UNHealthComponent::ApplyHealthDamage(AActor* DamagedActor, AController* Instigator, AActor* DamageCauser, float Damage)
{
	UNHealthComponent* HealthComp = GetHealthComponent(DamagedActor);
	if (IsValid(HealthComp))
	{
		if (HealthComp->GetIsInvulnerable() || !HealthComp->IsAlive())
			return;

		HealthComp->CurrentHealth = FMath::Max(HealthComp->CurrentHealth - Damage, 0.f);
		HealthComp->OnDamageTaken.Broadcast();
		HealthComp->PlayDamagedSound();

		if (HealthComp->CurrentHealth <= 0.f)
		{
			UNHealthComponent::KillActor(DamagedActor);
			return;
		}

		if (HealthComp->GetInvulnerabilityDuration() > 0.f)
			HealthComp->SetIsInvulnerable(true);

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
