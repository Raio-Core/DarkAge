// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Systems/DAAbilityTypes.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class DA_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:
	
	UPROPERTY(Replicated)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY()
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(ReplicatedUsing = OnRep_ProjectileTag)
	FGameplayTag ProjectileTag;
	
	UPROPERTY(ReplicatedUsing = OnRep_ProjectileMesh)
	TObjectPtr<UObject> ReplicatedMesh;
	
	UFUNCTION()
	void OnRep_ProjectileTag();
	
	UFUNCTION()
	void OnRep_ProjectileMesh();
	
public:
	
	AProjectileBase();
	
	void SetProjectileParams(const FProjectileParams& Params, const FGameplayTag& InProjectileTag = FGameplayTag());
	
	UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh.Get(); }
};
