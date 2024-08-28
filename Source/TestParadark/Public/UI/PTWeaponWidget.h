// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "PTWeaponWidget.generated.h"

class UTP_WeaponComponent;

UCLASS()
class TESTPARADARK_API UPTWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetupDataBinds(UTP_WeaponComponent* InComponent);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnDataChanged(FGameplayTag NewWeaponTag);

protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UTP_WeaponComponent> WeaponComponent;
};
