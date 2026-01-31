#include "Creatures/Components/ResidentComponent.h"

#include "Buildings/House.h"

void UResidentComponent::AssignToHouse(AHouse* NewHouse)
{
	House = NewHouse;
	HouseChanged.Broadcast(House);
}

void UResidentComponent::RemoveFromHouse()
{
	House = nullptr;
	HouseChanged.Broadcast(House);
}

bool UResidentComponent::HasHome() const
{
	return House != nullptr;
}

FVector UResidentComponent::GetHomeLocation() const
{
	if (!House) return FVector::Zero();
	
	return House->GetActorLocation();
}
