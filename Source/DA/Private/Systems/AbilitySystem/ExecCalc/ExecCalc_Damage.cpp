// Copyright 2026 RaioCore and Raioix. All Rights Reserved.

#include "Systems/AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "Systems/AbilitySystem/DAGameplayTags.h"
#include "Systems/AbilitySystem/Attributes/DAAttributeSet.h"

struct DADamageStatics
{
	// Source Capture
	
	// Target Capture
	DECLARE_ATTRIBUTE_CAPTUREDEF(IncomingHealthDamage) 
	
	DADamageStatics()
	{
		
		// Source Defines
		
		// Target Defines
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDAAttributeSet, IncomingHealthDamage, Target, false);
		
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
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	// Get raw damage value
	float Damage = EffectSpec.GetSetByCallerMagnitude(DAGameplayTags::Combat::Data_Damage);
	Damage = FMath::Max<float>(Damage, 0.0f);
	
	if (Damage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().IncomingHealthDamageProperty, EGameplayModOp::Additive, Damage));
	}
}
