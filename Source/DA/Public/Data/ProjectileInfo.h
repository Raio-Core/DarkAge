// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Systems/DAAbilityTypes.h"
#include "ProjectileInfo.generated.h"

/**
 * 
 */
UCLASS()
class DA_API UProjectileInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,FProjectileParams> ProjectileInfoMap;

};
