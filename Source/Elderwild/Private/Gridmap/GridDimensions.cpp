#include "Gridmap/GridDimensions.h"

FVector2D UGridDimensions::CenterAdjustment()
{
	float HalfTileLength = TileSize / 2;
	return FVector2D{HalfTileLength, HalfTileLength};
}

FVector2D UGridDimensions::CenterOfTileToGridLocation(FIntVector2 Coord)
{
	return CornerOfTileToGridLocation(Coord) + CenterAdjustment();
}

FVector2D UGridDimensions::CornerOfTileToGridLocation(FIntVector2 Coord)
{
	FVector GridLocation = GetOwner()->GetActorLocation();
	float TileCornerX = Coord.X * TileSize + GridLocation.X;
	float TileCornerY = Coord.Y * TileSize + GridLocation.Y;
	return FVector2D{TileCornerX, TileCornerY};
}

bool UGridDimensions::TileIsValid(const FIntVector2 Coord) const
{
	return (Coord.X >= 0 && Coord.X < NumRows) && (Coord.Y >= 0 && Coord.Y < NumCols);
}

FIntVector2 UGridDimensions::LocationToTile(FVector HitLocation) const
{
	if (!TileHasValidDimensions()) return FIntVector2(-1, -1);
		
	const FVector LocalHitLocation = HitLocation - GetOwner()->GetActorLocation();
	
	return LocalLocationToTile(LocalHitLocation);
}

FIntVector2 UGridDimensions::LocalLocationToTile(FVector LocalHitLocation) const
{
	FIntVector2 TileCornerLocation;
	TileCornerLocation.X = FMath::Floor((LocalHitLocation.X / GetGridWidth()) * NumRows);
	TileCornerLocation.Y = FMath::Floor((LocalHitLocation.Y / GetGridHeight()) * NumCols);

	return TileCornerLocation;
}

bool UGridDimensions::TileHasValidDimensions() const
{
	return NumRows > 0 && NumCols > 0;
}