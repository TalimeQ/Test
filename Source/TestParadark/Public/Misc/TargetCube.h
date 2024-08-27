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
	//We can always add overrides and move them to protected, there is no need to do that now
	void CheckDeath(const FOnAttributeChangeData& Data);

	// Display data change on UI
	void DisplayOnUI(const FOnAttributeChangeData& Data) const;
	// Spawn Health widget after being hit
	void TrySpawnHealthWidget();
	
protected:
	// This will also serve for collisions
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> TargetMesh;

	// Exposed for BP as read only, its easy to create and prototype effect that way
	// As i can quickly apply them in BP
	// This is ok as normally this object would only serve as a lab test dummy :)
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UPTAbilitySystemComponent> AbilitySystemComponent;

	// Basically assign any widget we fancy
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPTWorldWidget> HealthWidgetClass;


private:
	UPROPERTY()
	TObjectPtr<UPTWorldWidget> HealthWidget;
	
	UPROPERTY()
	const UPTAttributeSet* AttributeSet ;
};
