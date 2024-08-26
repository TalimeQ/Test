// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "TargetCube.generated.h"

class UPTAbilitySystemComponent;
class UPTAttributeSet;
class UPTWorldWidget;

UCLASS()
class TESTPARADARK_API ATargetCube : public AActor , public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// End implementation of IAbilitySystemInterface
	
	ATargetCube();
	
	//Start AActor override
	virtual void PostInitializeComponents() override;
	//End Aactor override

protected:

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	
private:

	void AdjustHealthData(const FOnAttributeChangeData& Data);
	
	void TrySpawnHealthWidget();
	
protected:
	// This will also serve for collisions
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> TargetMesh;

	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	TObjectPtr<UPTAbilitySystemComponent> AbilitySystemComponent;

	// Basically assign any widget we fancy
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPTWorldWidget> HealthWidgetClass;
	
private:
	UPROPERTY()
	UPTWorldWidget* HealthWidget;
	
	UPROPERTY()
	TWeakObjectPtr<UPTAttributeSet> AttributeSet;
};
