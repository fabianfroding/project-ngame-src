// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Actors/Components/NDamageFlashComponent.h"

#include "Pawns/Components/NHealthComponent.h"

UNDamageFlashComponent::UNDamageFlashComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNDamageFlashComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* OwningActor = GetOwner();
	if (!IsValid(OwningActor))
		return;

	if (UNHealthComponent* HealthComponent = Cast<UNHealthComponent>(OwningActor->GetComponentByClass(UNHealthComponent::StaticClass())))
		HealthComponent->OnDamaged.AddUniqueDynamic(this, &UNDamageFlashComponent::OnDamaged);
}

void UNDamageFlashComponent::OnDamaged_Implementation(float DamageAmount, AActor* DamageSource)
{
	GetWorld()->GetTimerManager().SetTimer(ResetFlashTimerHandle, this, &UNDamageFlashComponent::ResetFlashMaterial, FlashDuration, false);
}
