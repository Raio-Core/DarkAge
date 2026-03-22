// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "DAAbilityTypes.generated.h"

class AProjectileBase;
class UGameplayEffect;
class UAbilitySystemComponent;

USTRUCT()
struct FDAGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
public:
	
	bool IsCriticalHit() const {return bCriticalHit;}
	
	void SetIsCriticalHit(const bool InCriticalHit) {bCriticalHit = InCriticalHit;}
	
	static DA_API
	FDAGameplayEffectContext* GetEffetContext(FGameplayEffectContextHandle Handle);
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return  StaticStruct();
	}
	
	virtual FDAGameplayEffectContext* Duplicate() const override
	{
		FDAGameplayEffectContext* NewContext = new FDAGameplayEffectContext();
		*NewContext = *this;
		
		if (GetHitResult())
		{
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		
		return NewContext;
	}
	
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
	
private:
	
	UPROPERTY()
	bool bCriticalHit = false;
	
};

template<>
struct TStructOpsTypeTraits<FDAGameplayEffectContext> : TStructOpsTypeTraitsBase2<FDAGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

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

USTRUCT(BlueprintType)
struct FDamageEffectInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> AvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageEffect = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	float BaseDameage = 0.f;
	
	UPROPERTY(BlueprintReadWrite)
	float AbilityLevel = 1.f;

};