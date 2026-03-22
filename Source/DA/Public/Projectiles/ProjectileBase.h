// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Systems/AbilitySystem/DAAbilityTypes.h"
#include "ProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DA_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<USphereComponent> OverlapSphere;
	
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
	
protected:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:
	
	AProjectileBase();
	
	void SetProjectileParams(const FProjectileParams& Params, const FGameplayTag& InProjectileTag = FGameplayTag());
	
	UPROPERTY(BlueprintReadWrite)
	FDamageEffectInfo DamageEffectInfo;
	
};
