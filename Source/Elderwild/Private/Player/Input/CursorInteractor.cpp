#include "Player/Input/CursorInteractor.h"

#include "Player/Input/MouseModeWidget.h"
#include "Player/Input/MouseMode.h"


void UCursorInteractor::Initialize(APlayerController* InController, AGrid* InGrid)
{
	Controller = InController;
	Grid = InGrid;

	CreateMouseModeWidget();
}

void UCursorInteractor::UpdateHover()
{
	if (MouseMode)
	{
		MouseMode->Hover();
	}
}

void UCursorInteractor::HandleClick()
{
	if (MouseMode)
	{
		MouseMode->Click();
	}
}

void UCursorInteractor::ChangeMouseMode(TSubclassOf<UMouseMode> ModeClass)
{
	if (!ModeClass) return;

	MouseMode = NewObject<UMouseMode>(this, ModeClass);

	if (Controller && Grid)
	{
		MouseMode->Init(Controller, Grid);
	}
	
	OnMouseModeChanged.Broadcast(MouseMode);
}

void UCursorInteractor::CreateMouseModeWidget()
{
	if (MouseModeWidgetClass && Controller)
	{
		MouseModeWidget = CreateWidget<UMouseModeWidget>(Controller, MouseModeWidgetClass);
			
		if (MouseModeWidget) MouseModeWidget->AddToPlayerScreen();
	}
}
