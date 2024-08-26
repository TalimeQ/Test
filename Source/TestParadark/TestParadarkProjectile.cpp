// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestParadarkProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ATestParadarkProjectile::ATestParadarkProjectile() 
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATestParadarkProjectile::OnHit);		// set up a notification for when this component hits something blocking
	
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	
	RootComponent = CollisionComp;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	
	InitialLifeSpan = 3.0f;
}

void ATestParadarkProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Log,TEXT("Projectile :: Hit with actor: %s  occured"), *(GetNameSafe(OtherActor)))
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ApplyOnHitEffects(OtherActor);
		Destroy();
	}
}

void ATestParadarkProjectile::ApplyOnHitEffects(AActor* Actor)
{
	UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);
	if(TargetAbilitySystem != nullptr)
	{
		UE_LOG(LogTemp,Warning, TEXT("No ability system found for %s"),*GetNameSafe(Actor));
		return;
	}

	UE_LOG(LogTemp,Log,TEXT("Applying Gameplay Effects"));
	
	for(auto EffectClass : OnHitEffects)
	{
	//	TargetAbilitySystem->ApplyGameplayEffectToSelf()
	}
}
