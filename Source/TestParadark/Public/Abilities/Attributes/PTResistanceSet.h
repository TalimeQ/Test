// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Attributes/PTAttributeSet.h"
#include "PTResistanceSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/*
 * Potentially i would also add Min/Max customizable values
 * This could get us a system similar to the ARPGS like diablo where we could have resistance caps
 * Vulnerability caps etc.
 */
UCLASS()
class TESTPARADARK_API UPTResistanceSet : public UPTAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Resistance")
	FGameplayAttributeData PhysicalResistance = 0.0f;
	ATTRIBUTE_ACCESSORS(UPTResistanceSet,PhysicalResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Resistance")
	FGameplayAttributeData FireResistance = 0.0f;
	ATTRIBUTE_ACCESSORS(UPTResistanceSet,FireResistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Resistance")
	FGameplayAttributeData WaterResistance = 0.0f;
	ATTRIBUTE_ACCESSORS(UPTResistanceSet,WaterResistance);

};
