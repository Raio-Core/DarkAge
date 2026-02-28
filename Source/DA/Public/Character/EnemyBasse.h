// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/CharacterBasse.h"
#include "EnemyBasse.generated.h"

class UDAAttributeSet;
class UDAAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DA_API AEnemyBasse : public ACharacterBasse, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(ReplicatedUsing=OnRep_InitAttributes)
	bool bInitAttributes = false;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDAAbilitySystemComponent> DAAbilitySystemComp;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDAAttributeSet> DAAttributes;

	UFUNCTION()
	void OnRep_InitAttributes();
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void BindCallbacksToDependencies() override;
	virtual void InitClassDefaults() override;
	virtual void BroadcastInitialValues() override;

public:
	
	AEnemyBasse();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
};
