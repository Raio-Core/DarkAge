// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DAGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ADAGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ADAGameMode();
};



