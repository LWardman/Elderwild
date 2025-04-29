#include "Player/CursorInteractor.h"

#include "Player/CameraController.h"
#include "Player/BuildingModeWidget.h"
#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"


void UCursorInteractor::Initialize(ACameraController* InController, AGrid* InGrid)
{
	Controller = InController;
	Grid = InGrid;

	CreateMouseModeWidget();
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

	if (Grid)
	{
		switch(MouseMode)
		{
			case FMouseMode::DEFAULT:
				Grid->SetSelectionMaterialColour(Grid->SelectionColorInspect);
				Grid->IsInBuildMode = false;
				break;
						
			case FMouseMode::BUILDING:
				Grid->SetSelectionMaterialColour(Grid->SelectionColorBuildValid);
				Grid->IsInBuildMode = true;
				break;
		}
	}
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

void UCursorInteractor::CreateMouseModeWidget()
{
	UE_LOG(LogTemp, Display, TEXT("Step 1"));
	if (MouseModeWidgetClass && Controller)
	{
		
		UE_LOG(LogTemp, Display, TEXT("Step 2"));
		MouseModeWidget = CreateWidget<UBuildingModeWidget>(Controller, MouseModeWidgetClass);
			
		if (MouseModeWidget)
		{
			UE_LOG(LogTemp, Display, TEXT("Step 3"));
			MouseModeWidget->AddToPlayerScreen();
		}
	}
}
