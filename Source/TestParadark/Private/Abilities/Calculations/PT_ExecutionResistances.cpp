// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Calculations/PT_ExecutionResistances.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Attributes/PTAttributeSet.h"

// I wont lie im basically writing it step by step merging multiple tutorials and trying to make it readable/undestand it
// FML, learning GAS for this task was not really worth it
struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistances);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageBase);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPTAttributeSet,DamageBase,Source,false);
	
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPTAttributeSet,Health,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPTAttributeSet,Resistances,Target,false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DamageStatics;
	return DamageStatics;
}

UPT_ExecutionResistances::UPT_ExecutionResistances()
{
	RelevantAttributesToCapture.Add(DamageStatics().DamageBaseDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistancesDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
}

void UPT_ExecutionResistances::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                      FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//Cache the spec
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
 
	//Grab the tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
 
	//Setup our evaluate params
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	//Grab any damage resistances from the target
	float DamageResistance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageStatics().ResistancesDef, EvaluateParameters, DamageResistance);
	
	//Calculate the Outgoing Ability Damage. 
	float AbilityDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageStatics().DamageBaseDef, EvaluateParameters, AbilityDamage);

	float  DamageDone = AbilityDamage * FMath::Clamp(DamageResistance/100, -1.0f,1.0f);
	
	if(DamageDone < 0 )
	{
		DamageDone = 0;
	}
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty,EGameplayModOp::Additive, -DamageDone));
}
