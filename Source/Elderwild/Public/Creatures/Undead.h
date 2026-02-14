#pragma once

#include "CoreMinimal.h"
#include "Creatures/Creature.h"
#include "Undead.generated.h"

class UBuildingAssignmentComponent;
class ABuilding;

UCLASS()
class ELDERWILD_API AUndead : public ACreature
{
	GENERATED_BODY()
	
public:
	AUndead();
	
private:
	UPROPERTY(VisibleAnywhere)
	UBuildingAssignmentComponent* ResidentComponent;
	
	UFUNCTION()
	void OnHouseChanged(ABuilding* Building);
};
