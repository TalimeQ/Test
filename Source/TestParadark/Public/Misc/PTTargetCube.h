// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "PTTargetCube.generated.h"

class UPTAbilitySystemComponent;
class UPTAttributeSet;
class UPTWorldWidget;

UCLASS()
class TESTPARADARK_API APTTargetCube : public AActor , public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// End implementation of IAbilitySystemInterface
	
	APTTargetCube();
	
	//Start AActor override
	virtual void PostInitializeComponents() override;
	//End Aactor override

protected:

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	
private:

	void CheckDeath(const FOnAttributeChangeData& Data);
	
	void DisplayOnUI(const FOnAttributeChangeData& Data) const;
	
	void TrySpawnHealthWidget();
	
protected:
	// Mesh and collider, this will trigger OnHits
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> TargetMesh;

	// Ability system reference for ease of access 
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UPTAbilitySystemComponent> AbilitySystemComponent;

	// Widget class for health UI displayable after hit
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPTWorldWidget> HealthWidgetClass;


private:
	UPROPERTY()
	TObjectPtr<UPTWorldWidget> HealthWidget;
	
	UPROPERTY()
	const UPTAttributeSet* AttributeSet ;
};
