// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBasse.h"

#include "Data/CharacterClassInfo.h"
#include "Systems/AbilitySystem/DAAbilitySystemComponent.h"
#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"
#include "Systems/AbilitySystem/Libraries/DAAbilitySystemLibrary.h"


AEnemyBasse::AEnemyBasse()
{
	bReplicates = true;
	
	DAAbilitySystemComp = CreateDefaultSubobject<UDAAbilitySystemComponent>("AbilitySystemComponent");
	DAAbilitySystemComp->SetIsReplicated(true);
	DAAbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	DAAttributes = CreateDefaultSubobject<UDAAttributeSet>("Attributes");
}

void AEnemyBasse::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	
}

UAbilitySystemComponent* AEnemyBasse::GetAbilitySystemComponent() const
{
	return DAAbilitySystemComp;
}

void AEnemyBasse::InitAbilityActorInfo()
{
	if (IsValid(DAAbilitySystemComp) && IsValid(DAAttributes))
	{
		DAAbilitySystemComp->InitAbilityActorInfo(this, this);
		
		if (HasAuthority())
		{
			InitClassDefaults();
		}
	}
}

void AEnemyBasse::BindCallbacksToDependencies()
{
	if (IsValid(DAAbilitySystemComp) && IsValid(DAAttributes))
	{
		DAAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(DAAttributes->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)-> void
			{
				OnHealthChanged(Data.NewValue, DAAttributes->GetMaxHealth());
			});
	}
}

void AEnemyBasse::InitClassDefaults()
{
	if (!CharacterTag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("No Character Tag Selected In This Character %s"), *GetNameSafe(this));
	}
	else if (UCharacterClassInfo* ClassInfo = UDAAbilitySystemLibrary::GetCharacterClassDefaultInfo(this))
	{
		if (const FCharacterClassDefaultInfo* SelectedClass = ClassInfo->ClassDefaultInfoMap.Find(CharacterTag))
		{
			if (IsValid(DAAbilitySystemComp))
			{
				DAAbilitySystemComp->AddCharacterAbilities(SelectedClass->StartingAbilities);
				DAAbilitySystemComp->AddCharacterPassiveAbilities(SelectedClass->StartingPassives);
				DAAbilitySystemComp->InitializeDefaultAttributes(SelectedClass->DefaultAttributes);
			}
		}
	}
}
