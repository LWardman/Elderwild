#include "Player/Input/BuildMode.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"
#include "Gridmap/GridVisuals.h"
#include "Gridmap/OccupancyMap.h"
#include "Gridmap/SelectionTile.h"
#include "Logging/ControlsLog.h"

void UBuildMode::OnMouseModeEnter()
{
	Super::OnMouseModeEnter();
	
	if (AGrid* Grid = GetGrid())
	{
		Grid->CreateDisplayBuilding();
	}
}

void UBuildMode::Click()
{
	Super::Click();
	
	AGrid* Grid = GetGrid();

	if (!Grid || !Grid->GetGridDimensions()) return;
	
	FHitResult Hit = GetHitResultUnderCursor();
	if (Hit.IsValidBlockingHit())
	{
		const FIntVector2 GridTile = UGridDimensions::LocationToTile(Hit.Location, Grid);
		Grid->TryBuild(GridTile);
	}
}

void UBuildMode::Hover()
{
	Super::Hover();

	AGrid* Grid = GetGrid();
	if (!Grid || !Grid->GetGridDimensions() || !Grid->GetGridVisuals() || !Grid->GetSelectionTile()) return;
	
	FHitResult Hit = GetHitResultUnderCursor();
	if (Hit.IsValidBlockingHit())
	{
		Grid->HoverTile(Hit.Location);
		
		FIntVector2 Coord = UGridDimensions::LocationToTile(Hit.Location, Grid);
		TArray<FIntVector2> BuildingTiles = Grid->GetSelectionTile()->CalculateRelevantTileLocations(Coord);
		TArray<FIntVector2> ValidTiles;
		
		// TODO : This should probably be moved to AGrid
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

void UBuildMode::OnMouseModeExit()
{
	Super::OnMouseModeExit();
	
	if (AGrid* Grid = GetGrid())
	{
		UE_LOG(ControlsLog, Display, TEXT("Setting building data to empty"));
		Grid->DestroyDisplayBuilding();
	}
}
