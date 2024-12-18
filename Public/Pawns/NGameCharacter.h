// Copyright Epic Games, Inc. All Rights Reserved.
// Contributor: Fabian

#pragma once

#include "AbilitySystemInterface.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "Interfaces/NPawnBaseInterface.h"
#include "Logging/LogMacros.h"
#include "Types/NTypes.h"

#include "NGameCharacter.generated.h"

class UAbilitySystemComponent;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UGameplayEffect;
class UInputAction;
class UInputMappingContext;
class UNHealthComponent;
class UNPlayerWeaponsManagerComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDealtDamage, FNDamageEventData, DamageEventData);

UCLASS(config=Game)
class ANGameCharacter : public ACharacter, public INPawnBaseInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNPlayerWeaponsManagerComponent* PlayerWeaponsManagerComponent;

	//===== GAS Properties =====//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const class UNAbilityResourceAttributeSet* AbilityResourceAttributeSet;

	// Gameplay effect for when hostile actors collide with this pawn.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> HostileCollideGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	FGameplayTag HostileCollideDataTag;
	//===== End GAS Properties =====//

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDeath OnPlayerDeath;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDealtDamage OnPlayerDealtDamage;
	
public:
	ANGameCharacter();

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle) { bHasRifle = bNewHasRifle; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle() const { return bHasRifle; }

	UFUNCTION(BlueprintPure)
	UNHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintPure)
	UNPlayerWeaponsManagerComponent* GetPlayerWeaponsManagerComponent() const { return PlayerWeaponsManagerComponent; }

	FGameplayTag GetHostileCollideDataTag() const { return HostileCollideDataTag; }

	void OnDeath() const;

protected:
	virtual void BeginPlay();

	UFUNCTION()
	void OnAbilitySystemComponentInitialized(UActorComponent* Component, bool bReset);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	TSubclassOf<UGameplayEffect> GetHostileCollideGameplayEffect() const { return HostileCollideGameplayEffect; }

	UFUNCTION()
	void OnPlayerCollideWithEnemy(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

