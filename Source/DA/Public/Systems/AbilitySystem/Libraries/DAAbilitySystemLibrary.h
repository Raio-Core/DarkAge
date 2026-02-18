// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DAAbilitySystemLibrary.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class DA_API UDAAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure)
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure)
	static UCharacterClassInfo* GetCharacterClassDefaultInfo(const UObject* WorldContextObject);

};
