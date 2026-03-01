// Copyright 2026 RaioCore and Raioix. All Rights Reserved.


#include "Game/GameMode/DA_GameMode.h"

UCharacterClassInfo* ADA_GameMode::GetCharacterClassDefaultInfo() const
{
	return  ClassDefaults;
}

UProjectileInfo* ADA_GameMode::GetProjectileInfo() const
{
	return  ProjectileInfo;
}
