// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PTUiHealthInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPTUiHealthInterface : public UInterface
{
	GENERATED_BODY()
};

// Could be more generic (like an interface to work with attribute changes)
// I dont need that now 
class TESTPARADARK_API IPTUiHealthInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float CurrentHealth, float OldHealth, float MaxHealth);
};
