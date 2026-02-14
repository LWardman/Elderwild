#include "Creatures/Undead.h"

#include "Creatures/Components/BuildingAssignmentComponent.h"
#include "Creatures/CreatureController.h"
#include "Buildings/Building.h"

AUndead::AUndead()
{
	ResidentComponent = CreateDefaultSubobject<UBuildingAssignmentComponent>(TEXT("Resident Component"));
	ResidentComponent->BuildingChanged.AddDynamic(this, &AUndead::OnHouseChanged);
}

void AUndead::OnHouseChanged(ABuilding* Building)
{
	if (ACreatureController* CreatureController = Cast<ACreatureController>(GetController()))
	{
		CreatureController->UpdateHome(Building);
	}
}
