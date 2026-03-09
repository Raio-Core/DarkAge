// Copyright 2026 RaioCore and Raioix. All Rights Reserved.


#include "Systems/AbilitySystem/DAAbilitySystemComponent.h"

#include "Systems/AbilitySystem/Abilities/DAGameplayAbility.h"
#include "Systems/AbilitySystem/Abilities/ProjectileAbility.h"

void UDAAbilitySystemComponent::SetDynamicProjectile(const FGameplayTag& ProjectileTag)
{
	if (!ProjectileTag.IsValid()) return;
	
	if (!GetAvatarActor()->HasAuthority())
	{
		ServerSetDynamicProjectile(ProjectileTag);
		return;
	}
	
	if (ActiveProjectileAbility.IsValid())
	{
		ClearAbility(ActiveProjectileAbility);
	}
	
	if (IsValid(DynamicProjectileAbility))
	{
		FGameplayAbilitySpec Spec = FGameplayAbilitySpec(DynamicProjectileAbility, 1.f);
		if (UProjectileAbility* ProjectileAbility = Cast<UProjectileAbility>(Spec.Ability))
		{
			ProjectileAbility->ProjectileToSpawnTag = ProjectileTag;
			Spec.DynamicAbilityTags.AddTag(ProjectileAbility->InputTag);
			
			ActiveProjectileAbility = GiveAbility(Spec);
		}
	}
	
}

void UDAAbilitySystemComponent::ServerSetDynamicProjectile_Implementation(const FGameplayTag& ProjectileTag)
{
	SetDynamicProjectile(ProjectileTag);
}

void UDAAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1.f);
		
		if (UDAGameplayAbility* DAAbility = Cast<UDAGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(DAAbility->InputTag);
			GiveAbility(AbilitySpec);
		}
		
	}
}

void UDAAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& PassivesToGrant)
{
	
	for (const TSubclassOf<UGameplayAbility>& Ability : PassivesToGrant)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1.f);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UDAAbilitySystemComponent::InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& AttributeEffect)
{
	checkf(AttributeEffect, TEXT("No valid default attributes for this character %s"), *GetAvatarActor()->GetName());
	const FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(AttributeEffect, 1.f, ContextHandle);
	ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	OnAttributesGiven.Broadcast();
}

void UDAAbilitySystemComponent::AbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	ABILITYLIST_SCOPE_LOCK();

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			if (!Spec.IsActive())
			{
				TryActivateAbility(Spec.Handle);
			}
			else if (UGameplayAbility* Instance = Spec.GetPrimaryInstance())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle,
					Instance->GetCurrentActivationInfo().GetActivationPredictionKey());
			}
		}
	}
}

void UDAAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	ABILITYLIST_SCOPE_LOCK();
	
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			if (UGameplayAbility* Instance = Spec.GetPrimaryInstance())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle,
					Instance->GetCurrentActivationInfo().GetActivationPredictionKey());
			}
		}
	}
}
