#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PTWorldWidget.generated.h"

class USizeBox;

UCLASS()
class TESTPARADARK_API UPTWorldWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPTWorldWidget(const FObjectInitializer& ObjectInitializer);
	
	void SetAttachmentActor(AActor* InAttachment);

	//Begin UUserWidget override
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	//end UUserWidget override

private:
	void SetupBinds();
	
protected:
	/*
	 *	Exposed for designers, this is base class so potentially
	 *	A design member would like to adjust this offset as a base
	 *	also there might be a possibility he wants to move it using BP :)
	 */
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FVector WidgetOffset;

	/*
	 * Core of the layout, this thing will be moving the whole widget
	 * Its also exposed but by meta tag. This makes it mandatory so deisngers wont miss it 
	 */
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;	
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AActor> AttachmentActor;
};


