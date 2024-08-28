#include "Abilities/Calculations/PT_ExecutionResistances.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Attributes/PTAttributeSet.h"

// README
// Resistances implementation
// Based on https://www.thegames.dev/?p=165
// Potentially could be done with different attributes as different resistances.
// This however seems to be the cleanest way of doing it to me

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

	// Basically this will get all Resistances with Tag X and damage with Tag X aggregate them and then calculate final damage
	
	//Grab any damage resistances from the target
	float DamageResistance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageStatics().ResistancesDef, EvaluateParameters, DamageResistance);
	
	//Calculate the Outgoing Ability Damage. 
	float AbilityDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FDamageStatics().DamageBaseDef, EvaluateParameters, AbilityDamage);

	// We will clamp between 100% resistance and - 100% resistance (2x damage)
	float  DamageDone = AbilityDamage * FMath::Clamp(1 - DamageResistance / 100, 0.0f,2.0f);

	UE_LOG(LogTemp,Warning,TEXT("Ability Damage :%f, Target Resistances :%f  Final Damage : %f"),AbilityDamage,DamageResistance,DamageDone);
	
	if(DamageDone < 0 )
	{
		DamageDone = 0;
	}
	
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty,EGameplayModOp::Additive, -DamageDone));
}
