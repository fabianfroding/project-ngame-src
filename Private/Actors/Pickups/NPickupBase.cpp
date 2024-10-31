// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Actors/Pickups/NPickupBase.h"
#include "Kismet/GameplayStatics.h"

ANPickupBase::ANPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANPickupBase::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();

	if (PickupCollider != nullptr)
	{
		PickupCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANPickupBase::OnPickupColliderOverlap);
	}
}

void ANPickupBase::CreatePickupCollider()
{
	if (PickupComponent != nullptr)
	{
		PickupComponent->SetupAttachment(RootComponent);
		PickupComponent->SetSimulatePhysics(false);
		PickupComponent->SetEnableGravity(false);
		PickupComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		// Create and attach the Sphere Collider (equivalent to Collider in Unity)
		PickupCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupCollider"));
		PickupCollider->SetupAttachment(PickupComponent);

		// Set the collider to act as a trigger
		PickupCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // Trigger mode
		PickupCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		PickupCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Allow overlap with pawns (players)
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("ANPickupBase::CreatePickupCollider: PickupComponent not initialized! Failed to create collider for pickup %s"), *GetFName().ToString());
	}
}

void ANPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle bobbing
	const float TimeSeconds = GetWorld()->GetTimeSeconds();
	const float BobbingAnimationPhase = ((FMath::Sin(TimeSeconds * VerticalBobFrequency) * 0.5f) + 0.5f) * BobbingAmount;

	FVector NewPosition = StartPosition + FVector(0.f, 0.f, BobbingAnimationPhase);
	SetActorLocation(NewPosition);

	// Handle rotating
	FRotator RotationDelta(0.f, RotatingSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(FQuat(RotationDelta));
}

void ANPickupBase::PlayPickupFeedback()
{
	if (bHasPlayedFeedback)
		return;

	if (PickupSfx)
		UGameplayStatics::SpawnSoundAtLocation(this, PickupSfx, GetActorLocation());

	if (PickupVfxPrefab)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupVfxPrefab, GetActorLocation(), FRotator::ZeroRotator);

	bHasPlayedFeedback = true;
}

void ANPickupBase::OnPickedUp_Implementation(APlayerController* PlayerController)
{
	PlayPickupFeedback();
}

void ANPickupBase::OnPickupColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
		return;

	if (APawn* OtherPawn = Cast<APawn>(OtherActor))
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(OtherPawn->GetController()))
			OnPickedUp(PlayerController);
	}
}
