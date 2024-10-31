// Copyright HungryHusky Games 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Pawns/NGameCharacter.h"

#include "NWeapon.generated.h"

UCLASS()
class NGAME_API ANWeapon : public AActor
{
	GENERATED_BODY()

private:
	ANGameCharacter* Character;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ANGameProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

public:
	ANWeapon();

	UFUNCTION(BlueprintCallable)
	void AttachWeapon(ANGameCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable)
	void Fire();

	void ShowWeapon(const bool bShow);

protected:
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
