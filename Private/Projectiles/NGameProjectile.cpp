// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projectiles/NGameProjectile.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayEffectTypes.h"
#include "Components/SphereComponent.h"
#include <Pawns/Components/NHealthComponent.h>
#include "Pawns/NGameCharacter.h"

ANGameProjectile::ANGameProjectile() 
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ANGameProjectile::OnHit);

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;
}

void ANGameProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		UNHealthComponent* HitHealthComponent = UNHealthComponent::FindHealthComponent(Hit.GetActor());
		if (HitHealthComponent == nullptr)
			return;

		UAbilitySystemComponent* AbilitySystemComponent = HitHealthComponent->GetAbilitySystemComponent();
		if (AbilitySystemComponent == nullptr)
			return;
		
		FGameplayEffectSpecHandle GESpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			ProjectileDamageGameplayEffect, 1.f, FGameplayEffectContextHandle());

		GESpecHandle.Data->SetSetByCallerMagnitude(ProjectileDamageDataTag, -1.f); // TODO: Add ProjectileDamageAmount and use it instead of -1.f.
		HitHealthComponent->TakeDamage(GESpecHandle, GetInstigator());
		
		Destroy();
	}
}