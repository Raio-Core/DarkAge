// Copyright 2026 RaioCore and Raioix. All Rights Reserved.


#include "Systems/AbilitySystem/Libraries/DAAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "Systems/DAAbilityTypes.h"
#include "Game/GameMode/DA_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/AbilitySystem/DAGameplayTags.h"

UCharacterClassInfo* UDAAbilitySystemLibrary::GetCharacterClassDefaultInfo(const UObject* WorldContextObject)
{
		if (const ADA_GameMode* DAGameMode = Cast<ADA_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
		{
			return  DAGameMode->GetCharacterClassDefaultInfo();
		}
	
	return nullptr;
}

UProjectileInfo* UDAAbilitySystemLibrary::GetProjectileInfo(const UObject* WorldContextObject)
{
	if (const ADA_GameMode* DAGameMode = Cast<ADA_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return  DAGameMode->GetProjectileInfo();
	}
	
	return nullptr;
}

void UDAAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectInfo& DamageEffectInfo)
{
	FGameplayEffectContextHandle ContextHandle = DamageEffectInfo.SourceASC->MakeEffectContext();
	ContextHandle.AddSourceObject(DamageEffectInfo.AvatarActor);
	
	FGameplayEffectSpecHandle SpecHandle = DamageEffectInfo.SourceASC->MakeOutgoingSpec(DamageEffectInfo.DamageEffect, DamageEffectInfo.AbilityLevel, ContextHandle);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DAGameplayTags::Combat::Data_Damage, DamageEffectInfo.BaseDameage);
	if (IsValid(DamageEffectInfo.TargetASC))
	{
		DamageEffectInfo.TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	
}

