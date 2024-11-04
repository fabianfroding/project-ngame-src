// Copyright HungryHusky Games 2024
// Contributor: Fabian

#include "Weapons/NWeapon.h"

#include "Pawns/NGameCharacter.h"
#include "Projectiles/NGameProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

UNWeapon::UNWeapon()
{
	WeaponSettings.MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UNWeapon::AttachWeapon(ANGameCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (Character == nullptr || Character->GetHasRifle())
		return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	Character->SetHasRifle(true);

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(WeaponSettings.FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(WeaponSettings.FireAction, ETriggerEvent::Triggered, this, &UNWeapon::Fire);
		}
	}
}

void UNWeapon::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("UNWeapon::AttachWeapon:Fire"));
	if (Character == nullptr || Character->GetController() == nullptr)
		return;

	if (WeaponSettings.ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(WeaponSettings.MuzzleOffset);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorSpawnParams.Instigator = Character;

			World->SpawnActor<ANGameProjectile>(WeaponSettings.ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	if (WeaponSettings.FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, WeaponSettings.FireSound, Character->GetActorLocation());
	}

	if (WeaponSettings.FireAnimation != nullptr)
	{
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(WeaponSettings.FireAnimation, 1.f);
		}
	}
}

void UNWeapon::ShowWeapon(const bool bShow)
{

}

void UNWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
		return;

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(WeaponSettings.FireMappingContext);
		}
	}
}
