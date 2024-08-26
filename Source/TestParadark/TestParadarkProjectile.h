// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestParadarkProjectile.generated.h"

class UGameplayEffect;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class ATestParadarkProjectile : public AActor
{
	GENERATED_BODY()

public:
	ATestParadarkProjectile();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:
	void ApplyOnHitEffects(AActor* Actor);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* CollisionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> OnHitEffects;
};

