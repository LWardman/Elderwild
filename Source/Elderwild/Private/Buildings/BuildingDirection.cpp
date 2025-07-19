#include "Buildings/BuildingDirection.h"

ECompassDirection UBuildingDirection::Direction = ECompassDirection::South;

void UBuildingDirection::RotateClockwise()
{
	Direction = static_cast<ECompassDirection>(GetNextDirectionIndex());
	UE_LOG(LogTemp, Display, TEXT("Now facing %s"), *UEnum::GetValueAsString(Direction));
}

FRotator UBuildingDirection::DirectionToRotator(ECompassDirection CompassDirection)
{
	uint8 DirectionInt = static_cast<uint8>(CompassDirection);
	FRotator Rotation(0.0f, DirectionInt * 90.f, 0.0f);
	return Rotation;
}

FVector2D UBuildingDirection::CentreOffsetMultiplier(FVector2D Offset, ECompassDirection CompassDirection)
{
	switch (CompassDirection)
	{
	case ECompassDirection::North:
		return {-Offset.Y, -Offset.X};
	case ECompassDirection::East:
		return {Offset.X, -Offset.Y};
	case ECompassDirection::South:
		return {Offset.Y, Offset.X};
	case ECompassDirection::West:
		return {-Offset.X, Offset.Y};
	default:
		return {Offset.X, Offset.Y};
	}	
}

uint8 UBuildingDirection::GetNextDirectionIndex()
{
	return (static_cast<uint8>(Direction) + 1) % static_cast<uint8>(ECompassDirection::COUNT);
}

