// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Interfaces/PTShootingInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TestParadarkCharacter.generated.h"

class UPTGameplayAbilityBase;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UPTAbilitySystemComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATestParadarkCharacter : public ACharacter , public IPTShootingInterface
{
	GENERATED_BODY()

public:
	
	ATestParadarkCharacter();

protected:
	// Begin AActor override
	virtual void BeginPlay();
	// End AActor override
public:

	//Begin IPTShootingInterface implementation
	virtual const FVector GetBulletSpawnLocation_Implementation(const FRotator SpawnRotation) override;
	virtual const FRotator GetBulletSpawnRotation_Implementation() override;
	//End IPTShootingInterface implementation
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:

	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	// APawn override
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn override

private:
	void CreateAbilities();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

protected:
	/** Setup for abilities to add them in quicker fashion
	 *
	 *In case of gun it should probably add abilties dynamically on pickup
	 but we start simple :) **/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<TSubclassOf<UPTGameplayAbilityBase>> InitialAbilities;
	
private:
	/** Start simply then add abstraction if needed */
	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	TObjectPtr<UPTAbilitySystemComponent> AbilityComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
};

