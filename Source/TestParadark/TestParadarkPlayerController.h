// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestParadarkPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class TESTPARADARK_API ATestParadarkPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	
protected:
	// Begin Actor interface
	virtual void BeginPlay() override;
	// End Actor interface
};
