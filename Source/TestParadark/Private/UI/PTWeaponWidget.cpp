// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PTWeaponWidget.h"

#include "TestParadark/TP_WeaponComponent.h"

void UPTWeaponWidget::SetupDataBinds_Implementation(UTP_WeaponComponent* InComponent)
{
	WeaponComponent = InComponent;
	WeaponComponent->OnWeaponChanged.AddDynamic(this,&UPTWeaponWidget::OnDataChanged);
}