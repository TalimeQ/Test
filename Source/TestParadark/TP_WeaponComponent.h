// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class ATestParadarkCharacter;
class UAbilitySystemComponent;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPARADARK_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ChangeAmmoTypeAction;

	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(ATestParadarkCharacter* TargetCharacter);
	
	UFUNCTION(Category="Weapon")
	void Fire();
	
	UFUNCTION(Category="Weapon")
	void ChangeAmmo();

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// A simple implementation of shooting modes/weapons swapping.
	// In case of a normal project weapon/ammo swap would be a GAS ability that would block shooting till finished with a tag
	// I would prolly also do an attribute set for ammo that we are holding (as we can find ammo before we find a corresponding gun)
	// In case of supporting ammo then a CanActivate check in ability would be done.
	// I really want to keep it simple so his small project i would simply track index of an array that contains ability tags

	//Potential Modes, exposed so designers can assign them
	//Defaults only as weapons should be prefabs always
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<FGameplayTag> AvailableFiringModes;
	
private:

	int32 FiringModeIndex;
	
	UPROPERTY()
	TWeakObjectPtr<ATestParadarkCharacter> Character;
};
