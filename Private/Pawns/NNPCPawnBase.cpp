// Copyright HungryHusky Games 2024

#include "Pawns/NNPCPawnBase.h"

#include "AbilitySystemComponent.h"
#include "Actors/Components/NDamageFlashComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pawns/Components/NHealthComponent.h"

ANNPCPawnBase::ANNPCPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HealthComponent = CreateDefaultSubobject<UNHealthComponent>(TEXT("NHealthComponent"));
	DamageFlashComponent = CreateDefaultSubobject<UNDamageFlashComponent>(TEXT("NDamageFlashComponent"));

	AbilitySystemComponent->OnComponentActivated.AddUniqueDynamic(this, &ANNPCPawnBase::OnAbilitySystemComponentInitialized);
}

void ANNPCPawnBase::OnAbilitySystemComponentInitialized(UActorComponent* Component, bool bReset)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	check(ASC);
	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
	AbilitySystemComponent->OnComponentActivated.RemoveDynamic(this, &ANNPCPawnBase::OnAbilitySystemComponentInitialized);
}
