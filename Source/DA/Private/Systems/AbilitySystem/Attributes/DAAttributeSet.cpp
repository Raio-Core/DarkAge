// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"


void UDAAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, Health, COND_None, REPNOTIFY_Always)

	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
}

void UDAAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void UDAAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, Health, OldHealth);
}

void UDAAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, MaxHealth, OldMaxHealth);
}