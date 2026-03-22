// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#include "Systems/AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "Systems/AbilitySystem/DAAbilityTypes.h"
#include "Systems/AbilitySystem/DAGameplayTags.h"
#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"

struct DADamageStatics
{
	// Source Capture
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	
	// Target Capture
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Shield);

	DADamageStatics()
	{
		
		// Source Defines
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, CritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, CritDamage, Source, false);
		
		// Target Defines
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, IncomingDamage, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, DamageReduction, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, Shield, Target, false);
		
	}
};

static const DADamageStatics& DamageStatics()
{
	static DADamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	// Source Captures
	RelevantAttributesToCapture.Add(DamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	
	//Target Captures
	RelevantAttributesToCapture.Add(DamageStatics().IncomingDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().ShieldDef);
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.TargetTags =  EffectSpec.CapturedTargetTags.GetAggregatedTags();
	EvalParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	
	const FGameplayEffectContextHandle EffectContextHandle = EffectSpec.GetContext();
	FDAGameplayEffectContext* DAContext = FDAGameplayEffectContext::GetEffetContext(EffectContextHandle);
	
	// Get raw damage value
	float Damage = EffectSpec.GetSetByCallerMagnitude(DAGameplayTags::Combat::Data_Damage);
	Damage = FMath::Max<float>(Damage, 0.0f);
	
	// Source Capture
	float CritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritChanceDef, EvalParams, CritChance);
	CritChance = FMath::Max<float>(CritChance, 0.0f);
	
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, EvalParams, CritDamage);
	CritDamage = FMath::Max<float>(CritDamage, 0.0f);
	
	// Target Captures
	float  Shield = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ShieldDef, EvalParams, Shield);
	Shield = FMath::Max<float>(Shield, 0.0f);
	
	float DamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageReductionDef, EvalParams, DamageReduction);
	DamageReduction = FMath::Max<float>(DamageReduction, 0.0f);
	
	// Begin Calculation
	
	const bool bCriticalHit = FMath::RandRange(0, 100) < CritChance;
	Damage = bCriticalHit ? Damage + (CritDamage * 0.5) : Damage;
	DAContext->SetIsCriticalHit(bCriticalHit);
	
	
	if (Damage > 0.f && Shield > 0.f)
	{
		Damage *= (100 - DamageReduction) / 100.0f;
	}
	
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingDamageProperty, EGameplayModOp::Additive, Damage));
}
