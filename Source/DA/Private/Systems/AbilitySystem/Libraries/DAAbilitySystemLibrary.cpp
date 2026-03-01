// Copyright 2026 RaioCore and Raioix. All Rights Reserved.


#include "Systems/AbilitySystem/Libraries/DAAbilitySystemLibrary.h"

#include "Game/GameMode/DA_GameMode.h"
#include "Kismet/GameplayStatics.h"

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

