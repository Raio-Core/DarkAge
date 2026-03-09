// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/DAAbilitySystemInterface.h"
#include "Interfaces/InventoryInterface.h"
#include "DA_PlayerController.generated.h"

class UDAAbilitySystemComponent;
class UDAInputConfig;
class UDASystemsWidget;
class UInventoryWidgetController;
class UInputMappingContext;
class UUserWidget;
class UInventoryComponent;

/**
 * PlayerController with inventory and input mapping support
 */

UCLASS()
class DA_API ADA_PlayerController : public APlayerController, public IAbilitySystemInterface, public IInventoryInterface, public  IDAAbilitySystemInterface
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY()
	TObjectPtr<UDAAbilitySystemComponent> DAAbilitySystemComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Input")
	TObjectPtr<UDAInputConfig> DAInputConfig; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Replicated)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	UPROPERTY()
	TObjectPtr<UInventoryWidgetController> InventoryWidgetController;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Widgets")
	TSubclassOf<UInventoryWidgetController> InventoryWidgetControllerClass;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UDASystemsWidget> InventoryWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Widgets")
	TSubclassOf<UDASystemsWidget> InventoryWidgetClass;
	
	UDAAbilitySystemComponent* GetDAAbilitySystemComponent();
	
	
protected:
	
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;
	
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;
	
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;
	
	virtual void BeginPlay() override;
	
	bool ShouldUseTouchControls() const;

	
public:
	
	ADA_PlayerController();
	
	virtual void SetupInputComponent() override;
	
	// Implement Inventory Interface
	virtual UInventoryComponent* GetInventoryComponent_Implementation() const;
	
	// Implement DAAbilitySystemInterface
	virtual void SetDynamicProjectile_Implementation(const FGameplayTag& ProjectileTag) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UInventoryWidgetController* GetInventoryWidgetController();
	
	UFUNCTION(BlueprintCallable)
	void CreateInventoryWidget();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
};
