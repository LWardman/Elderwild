#include "Player/CursorInteractor.h"

#include "Player/CameraController.h"
#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"

void UCursorInteractor::Initialize(ACameraController* InController, AGrid* InGrid)
{
	Controller = InController;
	Grid = InGrid;
}

void UCursorInteractor::UpdateHover()
{
	checkf(Controller && Grid, TEXT("Nullptr in Cursor Interactor, UpdateHover()"));
	
	FHitResult Hit;
	if (Controller->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		Grid->HoverTile(Hit.Location);
	}
	else
	{
		Grid->UnhoverTile();
	}
}

void UCursorInteractor::HandleClick()
{
	// TODO : this is fine for a small number of modes, use inheritance if/when this gets too big.
	switch(MouseMode)
	{
		case FMouseMode::DEFAULT:
			ClickedInDefaultMode();
			break;
			
		case FMouseMode::BUILDING:
			ClickedInBuildMode();
			break;
	}
}

void UCursorInteractor::ChangeMouseMode(FMouseMode NewMouseMode)
{
	MouseMode = NewMouseMode;
}

void UCursorInteractor::ClickedInDefaultMode()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked in default mode"));
}

void UCursorInteractor::ClickedInBuildMode()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked in build mode"));
	checkf(Controller && Grid && Grid->GridDimensions, TEXT("Nullptr in Cursor Interactor, HandleClick()"));
	
	FHitResult Hit;
	if (Controller->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		const FIntVector2 GridTile = Grid->GridDimensions->LocationToTile(Hit.Location);
		Grid->TryBuild(GridTile);
	}
}