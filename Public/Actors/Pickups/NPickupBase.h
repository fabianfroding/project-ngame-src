// Copyright HungryHusky Games 2024
// Contributor: Fabian

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NPickupBase.generated.h"

UCLASS()
class NGAME_API ANPickupBase : public AActor
{
	GENERATED_BODY()

protected:

    // Frequency at which the item will move up and down
    UPROPERTY(EditAnywhere)
    float VerticalBobFrequency = 1.f;

    // Distance the item will move up and down
    UPROPERTY(EditAnywhere)
    float BobbingAmount = 1.f;

    // Rotation angle per second
    UPROPERTY(EditAnywhere)
    float RotatingSpeed = 360.f;

    // Sound played on pickup
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* PickupSfx;

    // VFX spawned on pickup
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParticleSystem* PickupVfxPrefab;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UPrimitiveComponent* PickupComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBoxComponent* PickupCollider;

    FVector StartPosition;
    bool bHasPlayedFeedback;
	
public:
	ANPickupBase();

	virtual void Tick(float DeltaTime) override;

	void PlayPickupFeedback();

protected:
	virtual void BeginPlay() override;

    void CreatePickupCollider();

	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp(APlayerController* PlayerController);
    virtual void OnPickedUp_Implementation(APlayerController* PlayerController);

    UFUNCTION()
    void OnPickupColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

};
