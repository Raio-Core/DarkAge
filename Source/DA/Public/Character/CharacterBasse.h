// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "CharacterBasse.generated.h"

UCLASS()
class DA_API ACharacterBasse : public ACharacter
{
	GENERATED_BODY()

private:
	

protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	virtual void BindCallbacksToDependencies();
	virtual void InitClassDefaults();
	
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	
	UPROPERTY(EditAnywhere, Category="Custom Values|Character Infop")
	FGameplayTag CharacterTag;

public:

	ACharacterBasse();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float CurrentHealth, float MaxHealth);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChanged(float CurrentStamina, float MaxStamina);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnShieldChanged(float CurrentShield, float MaxShield);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(float CurrentMana, float MaxMana);
	
};
