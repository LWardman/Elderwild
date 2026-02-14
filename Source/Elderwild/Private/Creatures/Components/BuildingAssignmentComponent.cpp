#include "Creatures/Components/BuildingAssignmentComponent.h"

#include "Buildings/Building.h"

void UBuildingAssignmentComponent::AssignToBuilding(ABuilding* NewBuilding)
{
	Building = NewBuilding;
	BuildingChanged.Broadcast(Building);
}

void UBuildingAssignmentComponent::RemoveFromBuilding()
{
	Building = nullptr;
	BuildingChanged.Broadcast(Building);
}

bool UBuildingAssignmentComponent::IsAssigned() const
{
	return Building != nullptr;
}

FVector UBuildingAssignmentComponent::GetBuildingLocation() const
{
	if (!Building) return FVector::Zero();
	
	return Building->GetActorLocation();
}
