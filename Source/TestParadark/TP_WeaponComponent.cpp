// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "TestParadarkCharacter.h"
#include "TestParadarkProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Abilities/PTAbilitySystemComponent.h"
#include "UI/PTWeaponWidget.h"

UTP_WeaponComponent::UTP_WeaponComponent()
{
	FiringModeIndex = 0;
	PrimaryComponentTick.bCanEverTick = true;
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if(!ensureAlwaysMsgf(AvailableFiringModes.Num(),TEXT("UTP_WeaponComponent has no firing modes, please fix it! Aborting shooting")))
	{
		return;
	}

	FGameplayTagContainer TagContainer;
	FGameplayTag CurrentAbility = AvailableFiringModes[FiringModeIndex];
	TagContainer.AddTag(CurrentAbility);
	
	auto* AbilitiesComp = Character->FindComponentByClass<UPTAbilitySystemComponent>();
	AbilitiesComp->TryActivateAbilitiesByTag(TagContainer);

	UE_LOG(LogTemp,Log,TEXT("Firing with the ability type of : %s"),*(CurrentAbility.ToString()));
}

void UTP_WeaponComponent::ChangeAmmo(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp,Log,TEXT("Swapping Weapon!"));

	int32 Direction = FMath::Sign(Instance.GetValue().Get<float>());
	
	FiringModeIndex += 1 * Direction;
	if(FiringModeIndex >= AvailableFiringModes.Num())
	{
		FiringModeIndex = 0;
	}
	else if(FiringModeIndex < 0)
	{
		FiringModeIndex = AvailableFiringModes.Num() - 1;
	}

	if(ensureAlwaysMsgf(AvailableFiringModes.Num(),TEXT("UTP_WeaponComponent has no firing modes, please fix it! Aborting shooting")))
	{
		FGameplayTag CurrentMode = AvailableFiringModes[FiringModeIndex];
		OnWeaponChanged.Broadcast(CurrentMode);

		UE_LOG(LogTemp,Log,TEXT("New Firing Mode : %s"),*(CurrentMode.ToString()));
	}
}

FGameplayTag UTP_WeaponComponent::GetCurrentFiringMode() const
{
	if(!ensureAlwaysMsgf(AvailableFiringModes.Num(),TEXT("UTP_WeaponComponent has no firing modes, please fix it! Aborting shooting")))
	{
		return  AvailableFiringModes[FiringModeIndex];
	}

	return FGameplayTag::EmptyTag;
}

void UTP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(AvailableFiringModes.Num())
	{
		// Display what firing mode we have at the moment
		FString DebugMsg = "Current Fire Mode : " + AvailableFiringModes[FiringModeIndex].ToString();
		GEngine->AddOnScreenDebugMessage(-1,0.0f,FColor::Red,*DebugMsg);
	}
}

void UTP_WeaponComponent::AttachWeapon(ATestParadarkCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	Character->SetHasRifle(true);
	Character->SetWeapon(this);
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
			EnhancedInputComponent->BindAction(ChangeAmmoTypeAction,ETriggerEvent::Triggered, this, &UTP_WeaponComponent::ChangeAmmo);
		}
	}

	CreateWeaponUI();
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}

void UTP_WeaponComponent::CreateWeaponUI()
{
	// Fuck that shit.
	// Seems like widget does not want to get into viewport
	// This also corruptend my BP somehow so 
	if(Widget == nullptr && ensureMsgf(WidgetClass,TEXT("Please assign valid widget class")))
	{
		Widget = CreateWidget<UPTWeaponWidget>(Character->GetWorld(),WidgetClass);
		Widget->SetupDataBinds(this);
		Widget->AddToViewport();
	}
}
