#include "Gridmap/OccupancyMap.h"


void UOccupancyMap::Init(int32 _GridWidth, int32 _GridHeight)
{
	GridWidth = _GridWidth;
	GridHeight = _GridHeight;
	
	for (int i = 0; i < GridWidth; i++)
	{
		for (int j = 0; j < GridHeight; j++)
		{
			Map.Add(FIntVector2(i, j), EMPTY);
		}
	}
}

FOccupancyState UOccupancyMap::GetTileOccupancyState(FIntVector2 Coord)
{
	if (!Map.Contains(Coord)) return OCCUPIED;
	return Map[Coord];
}

void UOccupancyMap::SetTileOccupancyState(FIntVector2 Coord, FOccupancyState State)
{
	Map[Coord] = State;
}
