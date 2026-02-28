// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "DAPlayerState.generated.h"

class UDAAttributeSet;
class UDAAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DA_API ADAPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDAAbilitySystemComponent> DAAbilitySystemComp;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDAAttributeSet> DAAttributes;
	
public:
	
	ADAPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure)
	UDAAbilitySystemComponent* GetDAAbilitySystemComponent() const;
	
	UFUNCTION(BlueprintPure)
	UDAAttributeSet* GetDAAttributes() const;

};
