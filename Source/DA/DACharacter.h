// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "DACharacter.generated.h"

class UDAAttributeSet;
class UDAAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
 
UCLASS(abstract)
class ADACharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDAAbilitySystemComponent> DAAbilitySystemComp;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDAAttributeSet> DAAttributes;
	
	UPROPERTY(EditAnywhere, Category="Custom Values|Character Infop")
	FGameplayTag CharacterTag;
	
	void InitAbilityActorInfo();
	void InitClassDefaults() const;
	void BindCallbacksToDependencies();
	
	UFUNCTION(BlueprintCallable)
	void BroadcastInitialValues();
	
protected:

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

public:
	
	ADACharacter();	
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float CurrentHealth, float MaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChanged(float CurrentStamina, float MaxStamina);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(float CurrentMana, float MaxMana);
	
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);
	
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();
	

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

