// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#include "Systems/AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "Systems/AbilitySystem/DAGameplayTags.h"
#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"

struct DADamageStatics
{
	// Source Capture
	
	// Target Capture
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingHealthDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingShieldDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Shield);

	DADamageStatics()
	{
		
		// Source Defines
		
		// Target Defines
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, IncomingHealthDamage, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, IncomingShieldDamage, Target, false);
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
	
	//Target Captures
	RelevantAttributesToCapture.Add(DamageStatics().IncomingHealthDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().IncomingShieldDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().ShieldDef);
	
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer* TargetTag = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.TargetTags = TargetTag;
	EvalParams.SourceTags = SourceTags;
	
	// Get raw damage value
	float Damage = EffectSpec.GetSetByCallerMagnitude(DAGameplayTags::Combat::Data_Damage);
	Damage = FMath::Max<float>(Damage, 0.0f);
	
	// Target Captures
	float  Shield = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeBonusMagnitude(DamageStatics().ShieldDef, EvalParams, Shield);
	Shield = FMath::Max<float>(Shield, 0.0f);
	
	float DamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeBonusMagnitude(DamageStatics().DamageReductionDef, EvalParams, DamageReduction);
	DamageReduction = FMath::Max<float>(DamageReduction, 0.0f);
	
	float OutShield = 0.f;
	
	if (Damage > 0.f && DamageReduction > 0.f)
	{
		Damage += (100 - DamageReduction) / 100 ;
		OutShield = Shield - Damage;
		
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingHealthDamageProperty, EGameplayModOp::Additive, Damage));
		
	}
	
	if (OutShield <= 0.f)
	{
		const float RemainderDamage = fabs(Shield - Damage);
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingHealthDamageProperty, EGameplayModOp::Additive, RemainderDamage));
	}
}
