#include "Buildings/BuildingDirection.h"

ECompassDirection UBuildingDirection::Direction = ECompassDirection::South;

void UBuildingDirection::RotateClockwise()
{
	Direction = static_cast<ECompassDirection>(GetNextDirectionIndex());
	UE_LOG(LogTemp, Display, TEXT("Now facing %s"), *UEnum::GetValueAsString(Direction));
}

uint8 UBuildingDirection::GetNextDirectionIndex()
{
	return (static_cast<uint8>(Direction) + 1) % static_cast<uint8>(ECompassDirection::COUNT);
}

