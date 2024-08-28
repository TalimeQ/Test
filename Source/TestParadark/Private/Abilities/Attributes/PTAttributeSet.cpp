// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Attributes/PTAttributeSet.h"

void UPTAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Potentially there is abstraction here to be extracted for simplicity
	if(Attribute == GetHealthAttribute())
	{
		UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
		
		float CurrentHealthMax = HealthMax.GetBaseValue();
		NewValue = FMath::Clamp(NewValue,0.0f,CurrentHealthMax);

		if(!FMath::IsNearlyEqual(Health.GetBaseValue(),NewValue))
		{
			AbilityComp->ApplyModToAttributeUnsafe(Attribute, EGameplayModOp::Override, NewValue);
		}
	}

	// Also do it for other params, maybe extract a function call as this will be similar to health change
	
	// if(Attribute == GetHealthMaxAttribute())
	// {
	// 	
	// }	
}
