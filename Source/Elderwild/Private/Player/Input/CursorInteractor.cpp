#include "Player/Input/CursorInteractor.h"

#include "Player/Input/MouseModeWidget.h"
#include "Player/Input/MouseMode.h"
#include "Player/Input/MouseModeFactory.h"

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

void UCursorInteractor::ChangeMouseMode(EMouseModeType ModeType)
{
 	UMouseMode* NewMode = UMouseModeFactory::Create(this, ModeType);
	if (!NewMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create MouseMode of type %d"), ModeType);
		return;	
	}

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
			
		if (MouseModeWidget) 
		{
			MouseModeWidget->AddToPlayerScreen();
			MouseModeWidget->SetCursorInteractor(this);
		}
	}
}
