// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/DAAbilityTypes.h"
#include "Systems/AbilitySystem/Abilities/DAGameplayAbility.h"
#include "ProjectileAbility.generated.h"

/**
 * 
 */
UCLASS()
class DA_API UProjectileAbility : public UDAGameplayAbility
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY()
	TObjectPtr<AActor>AvatarActorFromInfo;
	
	FProjectileParams CurrentProjectileParams;
	
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile();
	
public:
	
	UProjectileAbility();
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Projectile")
	FGameplayTag ProjectileToSpawnTag;
	
};
