// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PTGameplayAbilityShoot.h"
#include "Abilities/Interfaces/PTShootingInterface.h"
#include "GameFramework/Character.h"
#include "TestParadark/TestParadarkProjectile.h"

void UPTGameplayAbilityShoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!ensureMsgf(ProjectileClass,TEXT("Null projectile class assigned, please reassign it properly, aborting")))
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,false,true);
		return;
	}

	if(!ensureMsgf(ActorInfo->AvatarActor->Implements<UPTShootingInterface>(),TEXT("Actor: %s does not implement shooting interface, aborting"),*(ActorInfo->AvatarActor->GetName())))
	{
		EndAbility(Handle,ActorInfo,ActivationInfo,false,true);
		return;
	}
	
	const FRotator SpawnRotation = IPTShootingInterface::Execute_GetBulletSpawnRotation(ActorInfo->AvatarActor.Get());
	const FVector SpawnLocation = IPTShootingInterface::Execute_GetBulletSpawnLocation(ActorInfo->AvatarActor.Get(),SpawnRotation);
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Instigator = Cast<APawn>(GetOwningActorFromActorInfo());
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// In normal project this should be pooled
	GetWorld()->SpawnActor<ATestParadarkProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

	FTimerDelegate Delegate;
	Delegate.BindUObject(this,&UPTGameplayAbilityShoot::EndAbility,Handle,ActorInfo,ActivationInfo,false,false);


	// Blocking spamming of abilities, quick fix for it
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,Delegate,ShootDelay,false);
	
	// TODO :: This should me moved do cue/ or rather event/task and be trigger projectile after it ends
	// No time now however!
	
	// if (FireSound != nullptr)
	// {
	// 	UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	// }
	
	// if (FireAnimation != nullptr)
	// {
	// 	UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
	// 	if (AnimInstance != nullptr)
	// 	{
	// 		AnimInstance->Montage_Play(FireAnimation, 1.f);
	// 	}
	// }
}

