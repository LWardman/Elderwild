#include "Creatures/Resident.h"

void AResident::AssignToHouse(AHouse* NewHouse)
{
	House = NewHouse;
}

void AResident::RemoveFromHouse()
{
	House = nullptr;
}

bool AResident::HasAHome()
{
	return House != nullptr;
}
