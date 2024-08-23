// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PTShootingInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPTShootingInterface : public UInterface
{
	GENERATED_BODY()
};

class TESTPARADARK_API IPTShootingInterface
{
	GENERATED_BODY()

public:

	// Native so designers can adjust these to their desires
	// Also works with script the "non general cases approach"
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shooting")
	const FVector GetBulletSpawnLocation(const FRotator SpawnRotation);

	// Native so designers can adjust these to their desires
	// Also works with script the "non general cases approach"
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shooting")
	const FRotator GetBulletSpawnRotation();
	
};
