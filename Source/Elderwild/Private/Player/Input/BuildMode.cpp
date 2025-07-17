#include "Player/Input/BuildMode.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"
#include "Gridmap/GridVisuals.h"
#include "Gridmap/OccupancyMap.h"
#include "Gridmap/SelectionTile.h"

void UBuildMode::Click()
{
	Super::Click();

	if (!Grid || !Grid->GetGridDimensions()) return;
	
	FHitResult Hit;
	if (Controller && Controller->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		const FIntVector2 GridTile = UGridDimensions::LocationToTile(Hit.Location, Grid);
		Grid->TryBuild(GridTile);
	}
}

void UBuildMode::Hover()
{
	Super::Hover();

	if (!Grid || !Grid->GetGridDimensions() || !Grid->GetGridVisuals() || !Grid->GetSelectionTile()) return;
	
	FHitResult Hit;
	if (Controller && Controller->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		Grid->HoverTile(Hit.Location);
		
		FIntVector2 Coord = UGridDimensions::LocationToTile(Hit.Location, Grid);
		TArray<FIntVector2> BuildingTiles = Grid->GetSelectionTile()->CalculateRelevantTileLocations(Coord, {2, 3});
		TArray<FIntVector2> ValidTiles;
		
		if (Grid->GetOccupancyMap())
		{
			for (FIntVector2 Tile : BuildingTiles)
			{
				EOccupancyState TileState = Grid->GetOccupancyMap()->GetTileOccupancyState(Tile);

				if (TileState == EOccupancyState::EMPTY)
				{
					ValidTiles.Add(Tile);
				}
			}

			if (ValidTiles.Num() == BuildingTiles.Num())
			{
				Grid->SetSelectionMaterialColour(Grid->GetGridVisuals()->BuildValidColor);
			}
			else
			{
				Grid->SetSelectionMaterialColour(Grid->GetGridVisuals()->BuildInvalidColor);
			}
		}
	}
	else
	{
		Grid->UnhoverTile();
	}
}
