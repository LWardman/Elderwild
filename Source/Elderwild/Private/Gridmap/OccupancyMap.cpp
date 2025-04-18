#include "Gridmap/OccupancyMap.h"


void UOccupancyMap::Init(int32 _GridWidth, int32 _GridHeight)
{
	double Start = FPlatformTime::Seconds();
	
	GridWidth = _GridWidth;
	GridHeight = _GridHeight;

	Map.SetNum(GridHeight);

	for (int i = 0; i < GridHeight; i++)
	{
		Map[i].Init(EMPTY, GridWidth);
	}

	double Elapsed = FPlatformTime::Seconds() - Start;
	UE_LOG(LogTemp, Warning, TEXT("Init took %f seconds"), Elapsed);
}

FOccupancyState UOccupancyMap::GetTileOccupancyState(FIntVector2 Coord)
{
	if (!IndexIsValid(Coord)) return OCCUPIED;
	
	return Map[Coord.X][Coord.Y];
}

void UOccupancyMap::SetTileOccupancyState(FIntVector2 Coord, FOccupancyState State)
{
	if (!IndexIsValid(Coord)) return;
	Map[Coord.X][Coord.Y] = State;
}

bool UOccupancyMap::IndexIsValid(FIntVector2 Coord)
{
	return Coord.X < GridWidth && Coord.Y < GridHeight; 
}
