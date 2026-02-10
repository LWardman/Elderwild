#include "Creatures/Components/BuildingAssignmentComponent.h"

#include "Buildings/Building.h"

void UResidentComponent::AssignToBuilding(ABuilding* NewBuilding)
{
	Building = NewBuilding;
	BuildingChanged.Broadcast(Building);
}

void UResidentComponent::RemoveFromBuilding()
{
	Building = nullptr;
	BuildingChanged.Broadcast(Building);
}

bool UResidentComponent::IsAssigned() const
{
	return Building != nullptr;
}

FVector UResidentComponent::GetHomeLocation() const
{
	if (!Building) return FVector::Zero();
	
	return Building->GetActorLocation();
}
