// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/AbilitySystem/Abilities/ProjectileAbility.h"

#include "Data/ProjectileInfo.h"
#include "Interfaces/DAAbilitySystemInterface.h"
#include "Projectiles/ProjectileBase.h"
#include "Systems/AbilitySystem/Libraries/DAAbilitySystemLibrary.h"

UProjectileAbility::UProjectileAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UProjectileAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	AvatarActorFromInfo = GetAvatarActorFromActorInfo();
	
	if (!ProjectileToSpawnTag.IsValid() || !IsValid(AvatarActorFromInfo)) return;
	
	if (UProjectileInfo* ProjectileInfo = UDAAbilitySystemLibrary::GetProjectileInfo(GetAvatarActorFromActorInfo()))
	{
		CurrentProjectileParams = *ProjectileInfo->ProjectileInfoMap.Find(ProjectileToSpawnTag);
	}
}

void UProjectileAbility::SpawnProjectile()
{
	if (!IsValid(CurrentProjectileParams.ProjectileClass))
	{
		return;
	}
	
	if (USceneComponent* SpawnPointComp = IDAAbilitySystemInterface::Execute_SetDynamicSpawnPoint(AvatarActorFromInfo))
	{
		const FVector SpawnPoint = SpawnPointComp->GetComponentLocation();
		const FVector TargetLocation = AvatarActorFromInfo->GetActorForwardVector() * 10000;
		const FRotator TargetRotation = (TargetLocation - SpawnPoint).Rotation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnPoint);
		SpawnTransform.SetRotation(TargetRotation.Quaternion());
		
		if (AProjectileBase* SpawnedProjectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(CurrentProjectileParams.ProjectileClass, SpawnTransform))
		{
			SpawnedProjectile->SetProjectileParams(CurrentProjectileParams, ProjectileToSpawnTag);
			SpawnedProjectile->FinishSpawning(SpawnTransform);
		}
	}
}
