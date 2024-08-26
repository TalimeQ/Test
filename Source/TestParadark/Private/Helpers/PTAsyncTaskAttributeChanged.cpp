// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/PTAsyncTaskAttributeChanged.h"

UPTAsyncTaskAttributeChanged* UPTAsyncTaskAttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UPTAsyncTaskAttributeChanged* WaitForAttributeChangedTask = NewObject<UPTAsyncTaskAttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComp = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UPTAsyncTaskAttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

UPTAsyncTaskAttributeChanged * UPTAsyncTaskAttributeChanged::ListenForAttributesChange(UAbilitySystemComponent * AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UPTAsyncTaskAttributeChanged* WaitForAttributeChangedTask = NewObject<UPTAsyncTaskAttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComp = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UPTAsyncTaskAttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UPTAsyncTaskAttributeChanged::EndTask()
{
	if (IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UPTAsyncTaskAttributeChanged::AttributeChanged(const FOnAttributeChangeData & Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}