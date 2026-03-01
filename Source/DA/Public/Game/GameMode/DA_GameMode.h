// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/ProjectileInfo.h"
#include "GameFramework/GameMode.h"
#include "DA_GameMode.generated.h"

/**
 * 
 */

class UCharacterClassInfo;

UCLASS()
class DA_API ADA_GameMode : public AGameMode
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Values|Class Defaults")
	TObjectPtr<UCharacterClassInfo> ClassDefaults;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Values|Projectiles")
	TObjectPtr<UProjectileInfo> ProjectileInfo;
	
public:
	
	UCharacterClassInfo* GetCharacterClassDefaultInfo() const;
	UProjectileInfo* GetProjectileInfo() const;
	

	
};
