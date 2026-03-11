// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/AbilitySystem/Abilities/DAGameplayAbility.h"
#include "DADamageAbility.generated.h"

struct FDamageEffectInfo;
/**
 * 
 */
UCLASS()
class DA_API UDADamageAbility : public UDAGameplayAbility
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Damage Effect")
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Damage Effect")
	FScalableFloat BaseDamage;
	
public:
	
	void CaptureDagaeEffectInfo(AActor* TargetActor, FDamageEffectInfo& OutInfo);
	
	
};
