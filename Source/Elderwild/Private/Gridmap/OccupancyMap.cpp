#include "Gridmap/OccupancyMap.h"


void UOccupancyMap::Init(int32 _GridWidth, int32 _GridHeight)
{
	GridWidth = FMath::Max(0, _GridWidth);	// Ensures no negative dimensions are ever taken seriously.
	GridHeight = FMath::Max(0, _GridHeight);

	// Multithreaded 'for loop' for speed. Does 100x100 at 0.05s, compared to standard for loop at 1s
	Map.SetNum(GridHeight);
	ParallelFor(GridHeight, [this](int32 x)
	{
		Map[x].Init(EOccupancyState::EMPTY, GridWidth);
	});
}

EOccupancyState UOccupancyMap::GetTileOccupancyState(FIntVector2 Coord)
{
	if (!IndexIsValid(Coord)) return EOccupancyState::NOT_A_TILE;

	return Map[Coord.X][Coord.Y];
}

bool UOccupancyMap::AllTilesHaveState(TArray<FIntVector2> Tiles, EOccupancyState State)
{
	for (FIntVector2 Tile : Tiles)
	{
		if (GetTileOccupancyState(Tile) != State) return false;
	}
	return true;
}

void UOccupancyMap::SetTileOccupancyState(FIntVector2 Coord, EOccupancyState State)
{
	if (!IndexIsValid(Coord)) return;
	Map[Coord.X][Coord.Y] = State;
}

void UOccupancyMap::SetGroupTileOccupancyState(TArray<FIntVector2> Tiles, EOccupancyState State)
{
	for (FIntVector2 Tile : Tiles)
	{
		SetTileOccupancyState(Tile, State);
	}
}
bool UOccupancyMap::IndexIsValid(FIntVector2 Coord)
{
	return Map.IsValidIndex(Coord.X) && Map[Coord.X].IsValidIndex(Coord.Y); 
}
