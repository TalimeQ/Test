// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged,FGameplayTag, NewWeaponTag);

class ATestParadarkCharacter;
class UAbilitySystemComponent;
class UPTWeaponWidget;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPARADARK_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	
	/** Sets default values for this component's properties */
	UTP_WeaponComponent();
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(ATestParadarkCharacter* TargetCharacter);
	
	UFUNCTION(Category="Weapon")
	void Fire();
	
	UFUNCTION(Category="Weapon")
	void ChangeAmmo(const FInputActionInstance& Instance);

	// For UI
	UFUNCTION(BlueprintCallable,Category="Weapon")
	FGameplayTag GetCurrentFiringMode() const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void CreateWeaponUI();

public:
	// Taken from the starter content, i would probably put input into one component in Character
	// This would not make character class a bloat, and also keep it so that when repossesion happens the pawn will stop responding to component actions
	// And instead respond to new pawn (like changing from a character pawn to car pawn will change input stack so that old pawn does not react)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ChangeAmmoTypeAction;
	
	UPROPERTY(BlueprintAssignable)
	FOnWeaponChanged OnWeaponChanged;
	
protected:
	// A simple implementation of shooting modes/weapons swapping.
	// In case of a normal project weapon/ammo swap would be a GAS ability that would block shooting till finished with a tag
	// I would probably also do an attribute set for ammo that we are holding (as we can find ammo before we find a corresponding gun)
	// In case of supporting ammo then a CanActivate check in ability would be done.
	// I really want to keep it simple so here i just track a tag and swap it with mousewheel
	
	//Potential Modes, exposed so designers can assign them
	//Defaults only as weapons should be prefabs always
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<FGameplayTag> AvailableFiringModes;

	// Dunno about that one, i guess it should be spawned in the same place where all ui does spawn and then be bound
	// That would prolly bind all ui in one place with it being character, however we do a lot of shortcuts here
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPTWeaponWidget> WidgetClass;
	
private:
	int32 FiringModeIndex;

	UPROPERTY()
	TObjectPtr<UPTWeaponWidget> Widget;
	
	UPROPERTY()
	TWeakObjectPtr<ATestParadarkCharacter> Character;
};
