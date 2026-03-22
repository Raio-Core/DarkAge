// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/AbilitySystem/DAAbilitySystemGlobals.h"
#include "Systems/AbilitySystem/DAAbilityTypes.h"

FGameplayEffectContext* UDAAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FDAGameplayEffectContext();
}
