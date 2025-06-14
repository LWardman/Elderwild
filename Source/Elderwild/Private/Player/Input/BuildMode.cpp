#include "Player/Input/BuildMode.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"
#include "Gridmap/GridVisuals.h"
#include "Gridmap/OccupancyMap.h"


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

	if (!Grid || !Grid->GetGridDimensions() || !Grid->GetGridVisuals()) return;
	
	FHitResult Hit;
	if (Controller && Controller->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		Grid->HoverTile(Hit.Location);

		FIntVector2 Coord = UGridDimensions::LocationToTile(Hit.Location, Grid);
		if (Grid->GetOccupancyMap())
		{
			switch (Grid->GetOccupancyMap()->GetTileOccupancyState(Coord))
			{
				case EOccupancyState::EMPTY:
					Grid->SetSelectionMaterialColour(Grid->GetGridVisuals()->BuildValidColor);
					break;
				case EOccupancyState::OCCUPIED:
					Grid->SetSelectionMaterialColour(Grid->GetGridVisuals()->BuildInvalidColor);
					break;
				case EOccupancyState::NOT_A_TILE:
					break;
			}
		}
	}
	else
	{
		Grid->UnhoverTile();
	}
}
