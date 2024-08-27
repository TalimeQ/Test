// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "TestParadarkCharacter.h"
#include "TestParadarkProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Abilities/PTAbilitySystemComponent.h"


UTP_WeaponComponent::UTP_WeaponComponent()
{
	FiringModeIndex = 0;
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

	UE_LOG(LogTemp,Log,TEXT("Firing with the ability type of : %s"),*(CurrentAbility.ToString()));
	
	auto* AbilitiesComp = Character->FindComponentByClass<UPTAbilitySystemComponent>();
	AbilitiesComp->TryActivateAbilitiesByTag(TagContainer);
}

void UTP_WeaponComponent::ChangeAmmo()
{
	UE_LOG(LogTemp,Log,TEXT("Swapping Weapon!"));

	FiringModeIndex++;
	if(FiringModeIndex >= AvailableFiringModes.Num())
	{
		FiringModeIndex = 0;
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