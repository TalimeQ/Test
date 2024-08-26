// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PTWorldWidget.h"
#include "AbilitySystemComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"


UPTWorldWidget::UPTWorldWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WidgetOffset = FVector();
	AttachmentActor = nullptr;
}

void UPTWorldWidget::SetAttachmentActor(AActor* InAttachment)
{
	AttachmentActor = InAttachment;

	SetupBinds();
}

void UPTWorldWidget::SetupBinds()
{

}


void UPTWorldWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(AttachmentActor == nullptr)
	{
		RemoveFromParent();
		UE_LOG(LogTemp,Warning,TEXT("Attached actor for widget: %s is no longer valid, removing widget"),*GetNameSafe(this));
		return;
	}

	FVector2D ScreenPosition;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),AttachmentActor->GetActorLocation() + WidgetOffset,ScreenPosition))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;
		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}

