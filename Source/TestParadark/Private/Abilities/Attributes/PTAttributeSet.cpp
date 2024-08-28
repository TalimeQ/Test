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

	// We would have to clamp health again to health max if it changes somehow
	// For example we get a health max debuff, out of scope of this task but leaving comment so you know :)
	// Especially as i dont have any effects that do so
	// if(Attribute == GetHealthMaxAttribute())
	// {
	// 	
	// }	
}
