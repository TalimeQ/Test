
#include "Misc/TargetCube.h"
#include "Abilities/PTAbilitySystemComponent.h"
#include "Abilities/Attributes/PTAttributeSet.h"
#include "UI/PTWorldWidget.h"

ATargetCube::ATargetCube()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPTAbilitySystemComponent>("AbilitiesComp");
	AttributeSet = CreateDefaultSubobject<UPTAttributeSet>(TEXT("AttributeSetBase"));
	
	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = TargetMesh;
}

UAbilitySystemComponent* ATargetCube::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATargetCube::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATargetCube::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	TrySpawnHealthWidget();

	// Could be done in tick -> but ticks are hard to debug if the larger they get and also they underperform
	// In case of cool bindings from UI this is also not worth the trouble
	// 1. Lyra seems to create separate component just so they can display attributes to UI (which is meh imo)
	// 2. In GAS documentation he binds to data changes with ASync Tasks (which is again another wrapper, so fuck it)
	// So i went with simple function call as its the simplest and thus most elegant at this moment

	AdjustHealthData(Data);
}

void ATargetCube::AdjustHealthData(const FOnAttributeChangeData& Data)
{
	if(HealthWidget != nullptr)
	{
		float HealthMax = AttributeSet->GetHealthMax();
		float CurrentHealth = Data.NewValue;
		float OldHealth = Data.OldValue;

		// Interface call, I will only need one function from a health widget
		// creating a child for widget or putting it in component seems like overkill
		
	}
}

void ATargetCube::TrySpawnHealthWidget()
{
	if(!ensureMsgf(HealthWidgetClass, TEXT("Health Widget Class is missing from %s"), *GetNameSafe(this)))
	{
		return;
	}

	if(HealthWidget == nullptr)
	{
		HealthWidget = CreateWidget<UPTWorldWidget>(GetWorld(),HealthWidgetClass);
		HealthWidget->SetAttachmentActor(this);
		HealthWidget->AddToViewport(0);
	}
}

