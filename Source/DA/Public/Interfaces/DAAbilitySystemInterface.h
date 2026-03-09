// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DAAbilitySystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDAAbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DA_API IDAAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USceneComponent* SetDynamicSpawnPoint();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDynamicProjectile(const FGameplayTag& ProjectileTag);
	
};
