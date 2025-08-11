#pragma once

#include "CoreMinimal.h"
#include "Creatures/Creature.h"
#include "Resident.generated.h"

UCLASS()
class ELDERWILD_API AResident : public ACreature
{
	GENERATED_BODY()

public:
	void AssignToHouse(AHouse* NewHouse);

	void RemoveFromHouse();

	bool HasAHome();
	
private:	
	UPROPERTY()
	AHouse* House;
};
