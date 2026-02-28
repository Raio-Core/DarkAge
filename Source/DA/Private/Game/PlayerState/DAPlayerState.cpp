// Copyright 2026 RaioCore and Raioix. All Rights Reserved.


#include "Game/PlayerState/DAPlayerState.h"

#include "Systems/AbilitySystem/DAAbilitySystemComponent.h"
#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"

ADAPlayerState::ADAPlayerState()
{
	SetNetUpdateFrequency(100.f);
	SetMinNetUpdateFrequency(66.f);

	DAAbilitySystemComp = CreateDefaultSubobject<UDAAbilitySystemComponent>("AbilitySystemComp");
	DAAbilitySystemComp->SetIsReplicated(true);
	DAAbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	DAAttributes = CreateDefaultSubobject<UDAAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ADAPlayerState::GetAbilitySystemComponent() const
{
	return DAAbilitySystemComp;
}

UDAAbilitySystemComponent* ADAPlayerState::GetDAAbilitySystemComponent() const
{
	return DAAbilitySystemComp;
}

UDAAttributeSet* ADAPlayerState::GetDAAttributes() const
{
	return DAAttributes;
}
