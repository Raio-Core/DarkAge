// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBasse.h"

#include "Data/CharacterClassInfo.h"
#include "Net/UnrealNetwork.h"
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
	
	BindCallbacksToDependencies();
	InitAbilityActorInfo();
	
}

void AEnemyBasse::OnRep_InitAttributes()
{
	BroadcastInitialValues();
}

void AEnemyBasse::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AEnemyBasse, bInitAttributes);
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
			BroadcastInitialValues();
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
		
		DAAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(DAAttributes->GetShieldAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)-> void
			{
				OnShieldChanged(Data.NewValue, DAAttributes->GetMaxShield());
			});
		
		if (HasAuthority())
		{
			DAAbilitySystemComp->OnAttributesGiven.AddLambda(
				[this]
			{
				bInitAttributes = true;
			});
		}
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

void AEnemyBasse::BroadcastInitialValues()
{
	if (IsValid(DAAttributes))
	{
		OnHealthChanged(DAAttributes->GetHealth(), DAAttributes->GetMaxHealth());
		OnShieldChanged(DAAttributes->GetShield(), DAAttributes->GetMaxShield());
	}
}
