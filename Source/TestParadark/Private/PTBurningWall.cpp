// Fill out your copyright notice in the Description page of Project Settings.


#include "PTBurningWall.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"


APTBurningWall::APTBurningWall()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitiesComp");

	// Basically create an invisible wall that has to be put down with water so we can move on
	// I could make it to be overlappable instead of blocking but
	// 1. It requires a bit of logic for which i have no time for (overlap checks with player pawn, properly checking instigators etc)
	// 2. Implementing overlaps in bullet (same, i have on hits so lets just stick to that)
	// 3. It fulfills requirements for now :)
	HitBox = CreateDefaultSubobject<UBoxComponent>("Box Component");
	HitBox->SetCollisionResponseToAllChannels(ECR_Block);
}

void APTBurningWall::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AbilitySystem->RegisterGameplayTagEvent(RequiredTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&APTBurningWall::OnTagAdded);
}

void APTBurningWall::OnTagAdded(FGameplayTag AddedTag, int TagCount)
{
	// Potentially add a timer so they dont get destroyed/deactivated instantly and let some fancy animation play\
	// And either remove unbind by handle from AS and toggling off collision. This works so thats it
	Destroy();
}



