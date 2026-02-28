// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DAGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DA_API UDAGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category= "Custom Values|Input")
	FGameplayTag InputTag;
};
