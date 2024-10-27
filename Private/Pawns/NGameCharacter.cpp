// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pawns/NGameCharacter.h"

#include "AbilitySystemComponent.h"
#include "Projectiles/NGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayAbilitySystem/AttributeSets/NHealthAttributeSet.h"
#include "GameplayAbilitySystem/AttributeSets/NAbilityResourceAttributeSet.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Pawns/Components/NHealthComponent.h"
#include "Pawns/Components/NPlayerWeaponsManagerComponent.h"
#include "Pawns/NNPCPawnBase.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ANGameCharacter::ANGameCharacter()
{
	bHasRifle = false;
	//GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	HealthComponent = CreateDefaultSubobject<UNHealthComponent>(TEXT("NHealthComponent"));
	PlayerWeaponsManagerComponent = CreateDefaultSubobject<UNPlayerWeaponsManagerComponent>(TEXT("PlayerWeaponsManagerComponent"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ANGameCharacter::OnDeath() const
{

	OnPlayerDeath.Broadcast();
}

void ANGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (IsValid(Mesh1P))
		GetCapsuleComponent()->OnComponentHit.AddUniqueDynamic(this, &ANGameCharacter::OnComponentHit);

	if (IsValid(AbilitySystemComponent))
	{
		HealthAttributeSet = AbilitySystemComponent->GetSet<UNHealthAttributeSet>();
		AbilityResourceAttributeSet = AbilitySystemComponent->GetSet<UNAbilityResourceAttributeSet>();
	}
}

void ANGameCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ANGameCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANGameCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANGameCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANGameCharacter::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<ANNPCPawnBase>(OtherActor))
	{
		UNHealthComponent::ApplyHealthDamage(this, nullptr, OtherActor, 1.f);
		//HealthAttributeSet->Health
	}
}
