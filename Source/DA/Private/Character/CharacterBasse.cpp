// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBasse.h"


ACharacterBasse::ACharacterBasse()
{
	
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterBasse::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBasse::InitAbilityActorInfo()
{
	// Intentionally left blank
}

void ACharacterBasse::BindCallbacksToDependencies()
{
	// Intentionally left blank
}

void ACharacterBasse::InitClassDefaults()
{
	// Intentionally left blank
}

void ACharacterBasse::BroadcastInitialValues()
{
	// Intentionally left blank
}

