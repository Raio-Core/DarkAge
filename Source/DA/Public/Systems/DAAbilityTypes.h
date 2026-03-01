// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAAbilityTypes.generated.h"

class AProjectileBase;

USTRUCT()
struct FProjectileParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> ProjectileMesh;
	
	// Add Niagara Particle System here when able
	
	
	UPROPERTY(EditDefaultsOnly)
	float InitialSpeed = 1000;
	
	UPROPERTY(EditDefaultsOnly)
	float GravityScale = 1.f;
	
	UPROPERTY(EditDefaultsOnly)
	bool bShouldBounce = false;
	
	UPROPERTY(EditDefaultsOnly)
	float Bounciness = 0.6f;

};
