#include "Player/Input/InspectMode.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridVisuals.h"
#include "Buildings/BuildingData.h"

void UInspectMode::OnMouseModeEnter()
{
	Super::OnMouseModeEnter();
	
	const UBuildingData* EmptyBuildingData = GetDefault<UBuildingData>();
	
	AGrid* Grid = GetGrid();
	if (Grid && Grid->GetGridVisuals())
	{
		Grid->SetSelectionMaterialColour(Grid->GetGridVisuals()->InspectColor);
		Grid->SetBuildingData(EmptyBuildingData);
	}
}

void UInspectMode::Click()
{
	Super::Click();
	
	UE_LOG(LogTemp, Display, TEXT("Clicked in inspect mode"));
}

void UInspectMode::Hover()
{
	Super::Hover();

	AGrid* Grid = GetGrid();
	if (!Grid) return;
	
	FHitResult Hit = GetHitResultUnderCursor();
	if (Hit.IsValidBlockingHit())
	{
		Grid->HoverTile(Hit.Location);
	}
	else
	{
		Grid->UnhoverTile();
	}
}
