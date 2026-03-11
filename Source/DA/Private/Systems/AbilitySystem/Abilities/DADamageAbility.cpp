// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/AbilitySystem/Abilities/DADamageAbility.h"

#include  "AbilitySystemGlobals.h"
#include "Systems/DAAbilityTypes.h"

void UDADamageAbility::CaptureDagaeEffectInfo(AActor* TargetActor, FDamageEffectInfo& OutInfo)
{
	if (AActor* AvatarActorFromInfo = GetAvatarActorFromActorInfo())
	{
		OutInfo.AbilityLevel = GetAbilityLevel();
		OutInfo.AvatarActor = AvatarActorFromInfo;
		OutInfo.BaseDameage = BaseDamage.GetValueAtLevel(GetAbilityLevel());
		OutInfo.DamageEffect = DamageEffect;
		OutInfo.SourceASC = GetAbilitySystemComponentFromActorInfo();
		
		if (IsValid(TargetActor))
		{
			OutInfo.TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
		}
	}
}
