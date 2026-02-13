// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlayerState/DAPlayerState.h"

#include "Systems/AbilitySystem/DAAbilitySystemComponent.h"
#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"

ADAPlayerState::ADAPlayerState()
{
	NetUpdateFrequency = 100.f;
	MinNetUpdateFrequency = 66.f;

	DAAbilitySystemComp = CreateDefaultSubobject<UDAAbilitySystemComponent>("AbilitySystemComp");
	DAAbilitySystemComp->SetIsReplicated(true);
	DAAbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	DAAttributes = CreateDefaultSubobject<UDAAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ADAPlayerState::GetAbilitySystemComponent() const
{
	return DAAbilitySystemComp;
}

UDAAbilitySystemComponent* ADAPlayerState::GetDAbilitySystemComponent() const
{
	return DAAbilitySystemComp;
}

UDAAttributeSet* ADAPlayerState::GetDAAttributes() const
{
	return DAAttributes;
}
