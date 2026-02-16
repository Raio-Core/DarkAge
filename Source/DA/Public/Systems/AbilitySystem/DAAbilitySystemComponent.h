// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DAAbilitySystemComponent.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class DA_API UDAAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	
public:

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassivesToGrant);
	void InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& AttributeEffect);
	
	
};
