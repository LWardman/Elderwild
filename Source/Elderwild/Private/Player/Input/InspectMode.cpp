#include "Player/Input/InspectMode.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridVisuals.h"


void UInspectMode::Init(APlayerController* InController, AGrid* InGrid)
{
	Super::Init(InController, InGrid);

	if (Grid && Grid->GetGridVisuals())
	{
		Grid->SetSelectionMaterialColour(Grid->GetGridVisuals()->InspectColor);
	}
}

void UInspectMode::Click()
{
	Super::Click();
	
	UE_LOG(LogTemp, Display, TEXT("Clicked in default mode"));
}

void UInspectMode::Hover()
{
	Super::Hover();

	if (!Grid) return;
	
	FHitResult Hit;
	if (Controller && Controller->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		Grid->HoverTile(Hit.Location);
	}
	else
	{
		Grid->UnhoverTile();
	}
}
