// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"


class UGameplayAbility;
class UGameplayEffect;

USTRUCT()
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingPassives;

};

/**
 * 
 */

UCLASS()
class DA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
	
	
public:

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FCharacterClassDefaultInfo> ClassDefaultInfoMap; 
	
};
