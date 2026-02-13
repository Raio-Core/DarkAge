// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "DAPlayerState.generated.h"

class UDAAttributeSet;
class UDAAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DA_API ADAPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDAAbilitySystemComponent> DAAbilitySystemComp;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDAAttributeSet> DAAttributes;
	
public:
	
	ADAPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure)
	UDAAbilitySystemComponent* GetDAbilitySystemComponent() const;
	
	UFUNCTION(BlueprintPure)
	UDAAttributeSet* GetDAAttributes() const;

};
