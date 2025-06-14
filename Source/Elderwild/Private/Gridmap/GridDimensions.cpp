#include "Gridmap/GridDimensions.h"

#include "Gridmap/Grid.h"

UGridDimensions::UGridDimensions()
{
	// Passing default values into Init will sanitize them, in case some are set wrong.
	Init(NumRows, NumCols, TileSize, LineThickness);
}

void UGridDimensions::Init(int32 _NumRows, int32 _NumCols, int32 _TileSize, int32 _LineThickness)
{
	NumRows = FMath::Max(0, _NumRows);
	NumCols = FMath::Max(0, _NumCols);
	
	TileSize = FMath::Max(1, _TileSize);

	LineThickness = FMath::Max(0, _LineThickness);
}

FVector2D UGridDimensions::CenterOfTileToGridLocation(FIntVector2 Coord)
{
	return CornerOfTileToGridLocation(Coord) + CenterAdjustment();
}

FVector2D UGridDimensions::CornerOfTileToGridLocation(FIntVector2 Coord)
{
	FVector GridLocation = GetWorldLocation();
	
	float TileCornerX = Coord.X * TileSize + GridLocation.X;
	float TileCornerY = Coord.Y * TileSize + GridLocation.Y;
	return FVector2D{TileCornerX, TileCornerY};
}

bool UGridDimensions::TileIsValid(const FIntVector2 Coord) const
{
	return (Coord.X >= 0 && Coord.X < NumRows) && (Coord.Y >= 0 && Coord.Y < NumCols);
}

FIntVector2 UGridDimensions::LocationToTile(FVector HitLocation, AGrid* Grid)
{
	if (!Grid ||
		!Grid->GetGridDimensions() ||
		!Grid->GetGridDimensions()->GridHasValidDimensions()) return FIntVector2(-1, -1);
		
	const FVector LocalHitLocation = HitLocation - Grid->GetActorLocation();
	
	return Grid->GetGridDimensions()->LocalLocationToTile(LocalHitLocation);
}

bool UGridDimensions::GridHasValidDimensions() const
{
	return NumRows > 0 && NumCols > 0;
}

FVector2D UGridDimensions::CenterAdjustment()
{
	float HalfTileLength = TileSize / 2;
	return FVector2D{HalfTileLength, HalfTileLength};
}

FIntVector2 UGridDimensions::LocalLocationToTile(FVector LocalHitLocation) const
{
	FIntVector2 TileCornerLocation;
	TileCornerLocation.X = FMath::Floor((LocalHitLocation.X / GetGridWidth()) * NumCols);
	TileCornerLocation.Y = FMath::Floor((LocalHitLocation.Y / GetGridHeight()) * NumRows);

	return TileCornerLocation;
}

FVector UGridDimensions::GetWorldLocation() const
{
	if (GetOwner()) return GetOwner()->GetActorLocation();
	return FVector::ZeroVector;
}