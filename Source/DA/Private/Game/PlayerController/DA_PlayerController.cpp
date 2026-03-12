// Copyright 2026 RaioCore and Raioix. All Rights Reserved.


#include "Game/PlayerController/DA_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DA.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Game/PlayerState/DAPlayerState.h"
#include "Input/DASystemsInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Systems/AbilitySystem/DAAbilitySystemComponent.h"
#include "Systems/Inventory/InventoryComponent.h"
#include "UI/WidgetControllers/InventoryWidgetController.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "UI/DASystemsWidget.h"


UDAAbilitySystemComponent* ADA_PlayerController::GetDAAbilitySystemComponent()
{
	if (!IsValid(DAAbilitySystemComp))
	{
		if (const ADAPlayerState* DAPlayerState = GetPlayerState<ADAPlayerState>())
		{
			DAAbilitySystemComp = DAPlayerState->GetDAAbilitySystemComponent();
		}
	}
	return DAAbilitySystemComp;
}

void ADA_PlayerController::AbilityInputPressed(FGameplayTag InputTag)
{
	if (IsValid(GetDAAbilitySystemComponent()))
	{
		DAAbilitySystemComp->AbilityInputPressed(InputTag);
	}
}

void ADA_PlayerController::AbilityInputReleased(FGameplayTag InputTag)
{
	if (IsValid(GetDAAbilitySystemComponent()))
	{
		DAAbilitySystemComp->AbilityInputReleased(InputTag);
	}
}

void ADA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->BOwnerLocallyControlled = IsLocalController();
	}
	
	if (const ADAPlayerState* DAPlayerState = GetPlayerState<ADAPlayerState>())
	{
		DAAbilitySystemComp = DAPlayerState->GetDAAbilitySystemComponent();
	}
	
	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogDA, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ADA_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UDASystemsInputComponent* DAInputComp = Cast<UDASystemsInputComponent>(InputComponent))
	{
		DAInputComp->BindAbilityAction(DAInputConfig, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased);
	}
		
	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool ADA_PlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

ADA_PlayerController::ADA_PlayerController()
{
	bReplicates = true;
	
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
	InventoryComponent->SetIsReplicated(true);
}

UInventoryComponent* ADA_PlayerController::GetInventoryComponent_Implementation() const
{
	return InventoryComponent;
}

void ADA_PlayerController::SetDynamicProjectile_Implementation(const FGameplayTag& ProjectileTag, int32 AbilityLevel)
{
	if (IsValid(DAAbilitySystemComp))
	{
		DAAbilitySystemComp->SetDynamicProjectile(ProjectileTag, AbilityLevel);
	}
}

UAbilitySystemComponent* ADA_PlayerController::GetAbilitySystemComponent() const
{
	return DAAbilitySystemComp;
}

void ADA_PlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADA_PlayerController, InventoryComponent);
}

UInventoryWidgetController* ADA_PlayerController::GetInventoryWidgetController()
{
	if (!IsValid (InventoryWidgetController))
	{
		InventoryWidgetController = NewObject<UInventoryWidgetController>(this, InventoryWidgetControllerClass);
		InventoryWidgetController->SetOwningActor(this);
		InventoryWidgetController->BindCallbacksToDependencies();
	}
	
	return InventoryWidgetController;
}

void ADA_PlayerController::CreateInventoryWidget()
{
	if (UUserWidget* Widget = CreateWidget<UDASystemsWidget>(this, InventoryWidgetClass))
	{
		InventoryWidget = Cast<UDASystemsWidget>(Widget);
		InventoryWidget->SetWidgetController(GetInventoryWidgetController());
		InventoryWidgetController->BroadcastInitialValues();
		InventoryWidget->AddToViewport();
	}
}
