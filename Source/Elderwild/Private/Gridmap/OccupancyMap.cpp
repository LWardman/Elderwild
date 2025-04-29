#include "Gridmap/OccupancyMap.h"


void UOccupancyMap::Init(int32 _GridWidth, int32 _GridHeight)
{
	double Start = FPlatformTime::Seconds();
	
	GridWidth = _GridWidth;
	GridHeight = _GridHeight;

	// Multithreaded 'for loop' for speed. Does 100x100 at 0.05s, compared to standard for loop at 1s
	Map.SetNum(GridHeight);
	ParallelFor(GridHeight, [this](int32 x)
	{
		Map[x].Init(EOccupancyState::EMPTY, GridWidth);
	});

	double Elapsed = FPlatformTime::Seconds() - Start;
	UE_LOG(LogTemp, Warning, TEXT("Init took %f seconds"), Elapsed);
}

EOccupancyState UOccupancyMap::GetTileOccupancyState(FIntVector2 Coord)
{
	if (!IndexIsValid(Coord)) return EOccupancyState::OCCUPIED;

	return Map[Coord.X][Coord.Y];
}

void UOccupancyMap::SetTileOccupancyState(FIntVector2 Coord, EOccupancyState State)
{
	if (!IndexIsValid(Coord)) return;
	Map[Coord.X][Coord.Y] = State;
}

bool UOccupancyMap::IndexIsValid(FIntVector2 Coord)
{
	return Map.IsValidIndex(Coord.X) && Map[Coord.X].IsValidIndex(Coord.Y); 
}
