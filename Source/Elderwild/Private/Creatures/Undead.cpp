#include "Creatures/Undead.h"

#include "Creatures/Components/ResidentComponent.h"
#include "Creatures/CreatureController.h"
#include "Buildings/House.h"

AUndead::AUndead()
{
	ResidentComponent = CreateDefaultSubobject<UResidentComponent>(TEXT("Resident Component"));
	ResidentComponent->HouseChanged.AddDynamic(this, &AUndead::OnHouseChanged);
}

void AUndead::OnHouseChanged(AHouse* House)
{
	if (ACreatureController* CreatureController = Cast<ACreatureController>(GetController()))
	{
		CreatureController->UpdateHome(House);
	}
}
