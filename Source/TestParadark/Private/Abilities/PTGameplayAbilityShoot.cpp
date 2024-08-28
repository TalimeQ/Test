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

	// There might be shitton of projectiles here, normally i would use object pool on them/or any other actor that is spawned -> destroyed to mouch
	// Not doing it here as i dont care that much about performance in test task :)
	GetWorld()->SpawnActor<ATestParadarkProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

	FTimerDelegate Delegate;
	Delegate.BindUObject(this,&UPTGameplayAbilityShoot::EndAbility,Handle,ActorInfo,ActivationInfo,false,false);

	// TODO :: Might be a gameplay task for this, check later :)
	
	// Dont want it to be spammable, cooldown would probably do it also but i want to also block execution of other abilities while delaying tag removal
	// This ability applies tag that would block other potential abilities for time being
	// One of such abilities could be reload or weapon swap which should be blocked for the duration of ability
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

