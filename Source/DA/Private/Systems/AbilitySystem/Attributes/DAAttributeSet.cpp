// Copyright 2026 RaioCore and Raioix. All Rights Reserved.


#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "Systems/AbilitySystem/DAAbilityTypes.h"


void UDAAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Health
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	// Shield
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, MaxShield, COND_None, REPNOTIFY_Always);
	// Damage Reduction
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, DamageReduction, COND_None, REPNOTIFY_Always);
	// Crit Damage
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	// Crit Chance
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, CritChance, COND_None, REPNOTIFY_Always);
	// Stamina
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	// Mana
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDAAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	
}

void UDAAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	
	if (Data.EvaluatedData.Attribute == GetIncomingHealthDamageAttribute())
	{
		HandleIncomingHealthDamage(Data);
	}
	
	if (Data.EvaluatedData.Attribute == GetIncomingShieldDamageAttribute())
	{
		HandleIncomingShieldDamage(Data);
	}
	
}

void UDAAttributeSet::HandleIncomingHealthDamage(const FGameplayEffectModCallbackData& Data)
{
	const float LocalDamage = GetIncomingHealthDamage();
	SetIncomingHealthDamage(0.f);
	
	FGameplayEffectContextHandle ContextHandle = Data.EffectSpec.GetContext();
	FDAGameplayEffectContext* DAContext = FDAGameplayEffectContext::GetEffetContext(ContextHandle);
	FColor DebugColor = DAContext->IsCriticalHit() ? FColor::Red : FColor::Green;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DebugColor,
		FString::Printf(TEXT("Damage Dealt: %d"), FMath::TruncToInt(LocalDamage)));
	
	SetHealth(FMath::Clamp(GetHealth() - LocalDamage, 0.f, GetMaxHealth()));
}

void UDAAttributeSet::HandleIncomingShieldDamage(const FGameplayEffectModCallbackData& Data)
{
	const float LocalDamage = GetIncomingShieldDamage();
	SetIncomingShieldDamage(0.f);
	
	FGameplayEffectContextHandle ContextHandle = Data.EffectSpec.GetContext();
	FDAGameplayEffectContext* DAContext = FDAGameplayEffectContext::GetEffetContext(ContextHandle);
	FColor DebugColor = DAContext->IsCriticalHit() ? FColor::Red : FColor::Green;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DebugColor,
		FString::Printf(TEXT("Damage Dealt: %d"), FMath::TruncToInt(LocalDamage)));
	
	SetShield(FMath::Clamp(GetShield() - LocalDamage, 0.f, GetMaxShield()));
}

// Health
void UDAAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, Health, OldHealth);
}
void UDAAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, MaxHealth, OldMaxHealth);
}
// Shield
void UDAAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, Shield, OldShield);
}
void UDAAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, MaxShield, OldMaxShield);
}
// Damage Reduction
void UDAAttributeSet::OnRep_DamageReduction(const FGameplayAttributeData& OldDamageReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, DamageReduction, OldDamageReduction);
}

void UDAAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, CritChance, OldCritChance);
}

void UDAAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, CritChance, OldCritDamage);
}

// Stamina
void UDAAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, Stamina, OldStamina);
}
void UDAAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, MaxStamina, OldMaxStamina);
}
// Mana
void UDAAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, Mana, OldMana);
}
void UDAAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDAAttributeSet, MaxMana, OldMaxMana);
}
