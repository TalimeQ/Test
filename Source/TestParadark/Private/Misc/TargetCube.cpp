
#include "Misc/TargetCube.h"
#include "Abilities/PTAbilitySystemComponent.h"
#include "Abilities/Attributes/PTAttributeSet.h"
#include "UI/PTWorldWidget.h"
#include "UI/Interfaces/PTUiHealthInterface.h"

ATargetCube::ATargetCube()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPTAbilitySystemComponent>("AbilitiesComp");

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

	// TODO :: FIX
	// Generally i tried GAS documentation way of creating my attribute set and it auto assigning (and it worked!)
	// However instead of replacing it it basically left me with 2 instances of it which sucks
	// Normally i would use static class but it somehow does not work and i have neither time nor sanity to work with it for now
	TSubclassOf<UAttributeSet> AttributeSetClass = UPTAttributeSet::StaticClass();
	AttributeSet = Cast<UPTAttributeSet>(AbilitySystemComponent->GetAttributeSet(AttributeSetClass));
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).
	AddUObject(this,&ATargetCube::OnHealthChanged);
}

void ATargetCube::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	TrySpawnHealthWidget();
	// Could be done in tick -> but ticks are hard to debug if the larger they get and also they underperform
	// In case of cool bindings from UI this is also not worth the trouble
	// 1. Lyra seems to create separate component just so they can display attributes to UI and use delegates with it (which is meh imo)
	// 2. In GAS documentation he creates async task which binds to attribute change  (which is again another wrapper, and seems like overkill)
	// So i went with simple function call as its the simplest and thus most elegant at this moment

	DisplayOnUI(Data);
	CheckDeath(Data);
}

void ATargetCube::CheckDeath(const FOnAttributeChangeData& Data)
{
	if(FMath::IsNearlyZero(Data.NewValue))
	{
		Destroy();
	}
}

void ATargetCube::DisplayOnUI(const FOnAttributeChangeData& Data) const
{
	if(HealthWidget == nullptr)
	{
		return;
	}

	if(!ensureMsgf(HealthWidget->Implements<UPTUiHealthInterface>(),TEXT("Widget %s does not implement PTUiHealthInterface but is used as one that does"),*GetNameSafe(HealthWidget)))
	{
		return;
	}
	
	float HealthMax = AttributeSet->GetHealthMax();
	float CurrentHealth = Data.NewValue;
	float OldHealth = Data.OldValue;
	
	
	// Interface call, I will only need one function from a health widget
	// creating a child for widget or putting it in component to then make a call seems like overkill
	IPTUiHealthInterface::Execute_OnHealthChanged(HealthWidget,CurrentHealth,OldHealth,HealthMax);
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

