#include "Player/Input/CursorInteractor.h"

#include "Kismet/GameplayStatics.h"

#include "Player/Input/MouseModeWidget.h"
#include "Player/Input/MouseMode.h"
#include "Player/Input/MouseModeFactory.h"

void UCursorInteractor::BeginPlay()
{
	Super::BeginPlay();
	
	CreateMouseModeWidget();
}

void UCursorInteractor::UpdateHover()
{
	if (MouseMode) MouseMode->Hover();
}

void UCursorInteractor::HandleClick()
{
	if (MouseMode) MouseMode->Click();
}

void UCursorInteractor::ChangeMouseMode(EMouseModeType ModeType)
{
	if (MouseMode) MouseMode->OnMouseModeExit();
	
	if (UMouseMode* NewMode = UMouseModeFactory::Create(this, ModeType))
	{
		MouseMode = NewMode;
		MouseMode->OnMouseModeEnter();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create MouseMode of type %d"), ModeType);
	}
}

void UCursorInteractor::CreateMouseModeWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
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
