// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PT_ExecutionResistances.generated.h"

/**
 * 
 */
UCLASS()
class TESTPARADARK_API UPT_ExecutionResistances : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UPT_ExecutionResistances();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
