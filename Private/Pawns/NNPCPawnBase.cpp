// Copyright HungryHusky Games 2024

#include "Pawns/NNPCPawnBase.h"

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

	HealthComponent = CreateDefaultSubobject<UNHealthComponent>(TEXT("NHealthComponent"));
	DamageFlashComponent = CreateDefaultSubobject<UNDamageFlashComponent>(TEXT("NDamageFlashComponent"));
}
