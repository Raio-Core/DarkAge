// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#include "Character/DACharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DA.h"
#include "Data/CharacterClassInfo.h"
#include "Game/PlayerState/DAPlayerState.h"
#include "Systems/AbilitySystem/DAAbilitySystemComponent.h"
#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"
#include "Systems/AbilitySystem/Libraries/DAAbilitySystemLibrary.h"

ADACharacter::ADACharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	DynamicProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnPoint");
	DynamicProjectileSpawnPoint->SetupAttachment(RootComponent);

}

USceneComponent* ADACharacter::SetDynamicSpawnPoint_Implementation()
{
	return DynamicProjectileSpawnPoint;
}

void ADACharacter::InitAbilityActorInfo()
{
	if (ADAPlayerState* DAPlayerState = GetPlayerState<ADAPlayerState>())
	{
		DAAbilitySystemComp = DAPlayerState->GetDAAbilitySystemComponent();
		DAAttributes = DAPlayerState->GetDAAttributes();
		
		if (IsValid(DAAbilitySystemComp))
		{
			DAAbilitySystemComp->InitAbilityActorInfo(DAPlayerState, this);
			BindCallbacksToDependencies();
		
			if (HasAuthority())
			{
				InitClassDefaults();
			}
		}
	}
}

void ADACharacter::InitClassDefaults()
{
	if (!CharacterTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Character Tag Selected In This Character %s"), *GetNameSafe(this))
	}
	else if (UCharacterClassInfo* ClassInfo = UDAAbilitySystemLibrary::GetCharacterClassDefaultInfo(this))
	{
		if (const FCharacterClassDefaultInfo* SelectedClassInfo = ClassInfo->ClassDefaultInfoMap.Find(CharacterTag))
		{
			if (IsValid(DAAbilitySystemComp))
			{
				DAAbilitySystemComp->AddCharacterAbilities(SelectedClassInfo->StartingAbilities);
				DAAbilitySystemComp->AddCharacterPassiveAbilities(SelectedClassInfo->StartingPassives);
				DAAbilitySystemComp->InitializeDefaultAttributes(SelectedClassInfo->DefaultAttributes);
			}
		}
	}
}

void ADACharacter::BindCallbacksToDependencies()
{
	if (IsValid(DAAbilitySystemComp) && IsValid(DAAttributes))
	{
		DAAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(DAAttributes->GetHealthAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				OnHealthChanged(Data.NewValue, DAAttributes->GetMaxHealth());
			});
		
		DAAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(DAAttributes->GetStaminaAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
			{
				OnStaminaChanged(Data.NewValue, DAAttributes->GetMaxStamina());
			});
		
		DAAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(DAAttributes->GetManaAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
			{
				OnManaChanged(Data.NewValue, DAAttributes->GetMaxMana());
			});
	}
}

void ADACharacter::BroadcastInitialValues()
{
	if (IsValid(DAAttributes))
	{
		OnHealthChanged(DAAttributes->GetHealth(), DAAttributes->GetMaxHealth());
		OnStaminaChanged(DAAttributes->GetStamina(), DAAttributes->GetMaxStamina());
		OnManaChanged(DAAttributes->GetMana(), DAAttributes->GetMaxMana());
	}
}

void ADACharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADACharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (HasAuthority())
	{
		InitAbilityActorInfo();
	}
}

void ADACharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	InitAbilityActorInfo();
}

UAbilitySystemComponent* ADACharacter::GetAbilitySystemComponent() const
{
	return DAAbilitySystemComp;
}

void ADACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADACharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADACharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADACharacter::Look);
	}
	else
	{
		UE_LOG(LogDA, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADACharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	DoMove(MovementVector.X, MovementVector.Y);
}

void ADACharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ADACharacter::DoMove(const float Right, const float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ADACharacter::DoLook(const float Yaw, const float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ADACharacter::DoJumpStart()
{
	Jump();
}

void ADACharacter::DoJumpEnd()
{
	StopJumping();
}
