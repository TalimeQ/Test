// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PTAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TESTPARADARK_API UPTAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health = 100.0f;
	ATTRIBUTE_ACCESSORS(UPTAttributeSet,Health);
	
	// Exposing health max both for edition and ease of acces in other BPS
	// Later we could add debuffs to HealthMax similarly to for example Grimoires from WH:Vermintide
	// Not adding Min value as for health it would be always 0.0f
	UPROPERTY(BlueprintReadOnly, Category = "HealthMax")
	FGameplayAttributeData HealthMax = 100.0f;
	ATTRIBUTE_ACCESSORS(UPTAttributeSet,HealthMax);

	// The gist of how i would do it is here
	UPROPERTY(BlueprintReadOnly, Category = "Resistances")
	FGameplayAttributeData Resistances = 0.0f;
	ATTRIBUTE_ACCESSORS(UPTAttributeSet,Resistances);

	// Constant damage for ease and quick of use
	// Could then be potentially adjusted with for example effects (weapon upgrades)
	UPROPERTY(BlueprintReadOnly, Category = "DamageBase")
	FGameplayAttributeData DamageBase = 10.0f;
	ATTRIBUTE_ACCESSORS(UPTAttributeSet,DamageBase);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
