// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DAAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttributesGiven);
/**
 * 
 */
UCLASS()
class DA_API UDAAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
private:
	
	
	FGameplayAbilitySpecHandle ActiveProjectileAbility;
	
	UPROPERTY(EditDefaultsOnly, Category="Custom Values|Projectile Ability")
	TSubclassOf<UGameplayAbility> DynamicProjectileAbility;

	UFUNCTION(Server, Reliable)
	void ServerSetDynamicProjectile(const FGameplayTag& ProjectileTag, int32 AbilityLevel);
	
public:
	
	FOnAttributesGiven OnAttributesGiven;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassivesToGrant);
	void InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& AttributeEffect);
	
	void AbilityInputPressed(const FGameplayTag& InputTag);
	void AbilityInputReleased(const FGameplayTag& InputTag);
	
	void SetDynamicProjectile(const FGameplayTag& ProjectileTag, int32 AbilityLevel = 1);
	
};
