// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "PTBurningWall.generated.h"


class UAbilitySystemComponent;
class UBoxComponent;

//This class could be more generic
//Like TagResponse actor or something :)
// Potentially i could also make them share the base with PTTargetCube
// But it works now, and adding abstraction makes future changes harder
UCLASS()
class TESTPARADARK_API APTBurningWall : public AActor
{
	GENERATED_BODY()
	
public:	
	APTBurningWall();

protected:
	// Begin AActor Override
	virtual void PostInitializeComponents() override;
	// End AActor Override

	void OnTagAdded(FGameplayTag AddedTag, int TagCount);
	
protected:
	// For ease of acces, and quick testing
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	// Hitbox of this component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> HitBox;

	// Tag that we will act upon
	UPROPERTY(EditAnywhere, Category = "Abilities")
	FGameplayTag RequiredTag;
};
