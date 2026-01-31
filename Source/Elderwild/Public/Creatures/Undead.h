#pragma once

#include "CoreMinimal.h"
#include "Creatures/Creature.h"
#include "Undead.generated.h"

class UResidentComponent;
class AHouse;

UCLASS()
class ELDERWILD_API AUndead : public ACreature
{
	GENERATED_BODY()
	
public:
	AUndead();
	
private:
	UPROPERTY(VisibleAnywhere)
	UResidentComponent* ResidentComponent;
	
	UFUNCTION()
	void OnHouseChanged(AHouse* House);
};
