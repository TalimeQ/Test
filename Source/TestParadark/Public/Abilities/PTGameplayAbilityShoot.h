
#pragma once

#include "CoreMinimal.h"
#include "Abilities/PTGameplayAbilityBase.h"
#include "PTGameplayAbilityShoot.generated.h"

class ATestParadarkProjectile;

/* Its a good thing to code general cases (and shooting is general per se, we can have multiple weapons reusing this one) and to script non generic cases
* So the idea here is to implement generic shooting in this class then move specific implementations to BP where they can be accesed by design more easily
**/
UCLASS()
class TESTPARADARK_API UPTGameplayAbilityShoot : public UPTGameplayAbilityBase
{
	GENERATED_BODY()
	
public:
	// Start UPTGameplayAbilityBase override
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	// End UPTGameplayAbilityBase override

protected:
	// Exposed so we can create multiple shoots that fire different projectiles (healing/etc)
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<ATestParadarkProjectile> ProjectileClass;

	// Delay between shoots
	//~Normally that would be a Cooldown that starts after ability
	//~However i would need to create an event that plays anim and then removes tag, then apply cooldown, too much hassle for now 
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float ShootDelay = 0.2f;

private:
	FTimerHandle TimerHandle;
};
