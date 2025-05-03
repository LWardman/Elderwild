#include "Player/CursorInteractor.h"

#include "Player/MouseModeWidget.h"
#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"


void UCursorInteractor::Initialize(APlayerController* InController, AGrid* InGrid)
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
	// Fine for a small number of modes, when this gets over 3 cases then refactor.
	switch(MouseMode)
	{
		case EMouseMode::DEFAULT:
			ClickedInDefaultMode();
			break;
			
		case EMouseMode::BUILDING:
			ClickedInBuildMode();
			break;
	}
}

void UCursorInteractor::ChangeMouseMode(EMouseMode NewMouseMode)
{
	MouseMode = NewMouseMode;

	if (Grid)
	{
		Grid->MouseMode = NewMouseMode;
		Grid->SetSelectionMaterialFromMouseMode();
	}
}

void UCursorInteractor::ClickedInDefaultMode()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked in default mode"));
}

void UCursorInteractor::ClickedInBuildMode()
{
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
	if (MouseModeWidgetClass && Controller)
	{
		MouseModeWidget = CreateWidget<UMouseModeWidget>(Controller, MouseModeWidgetClass);
			
		if (MouseModeWidget) MouseModeWidget->AddToPlayerScreen();
	}
}
