#pragma once

#include "CoreMinimal.h"
#include "Creatures/Creature.h"
#include "Resident.generated.h"

UCLASS()
class ELDERWILD_API AResident : public ACreature // TODO : this might not play well as ACreature, consider UObject or ActorComponent instead
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
