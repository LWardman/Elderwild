#include "Player/MouseModeWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "Player/CameraController.h"
#include "Player/CursorInteractor.h"


void UMouseModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DefaultButton)
	{
		DefaultButton->OnReleased.AddDynamic(this, &UMouseModeWidget::OnDefaultButtonPressed);
	}
	if (BuildButton)
	{
		BuildButton->OnReleased.AddDynamic(this, &UMouseModeWidget::OnBuildButtonPressed);
	}

	SetCursorInteractor();
}

void UMouseModeWidget::OnDefaultButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Default mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(EMouseMode::DEFAULT);
	}
}

void UMouseModeWidget::OnBuildButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Build mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(EMouseMode::BUILDING);
	}
}

void UMouseModeWidget::SetCursorInteractor()
{
	APlayerController* FoundController = UGameplayStatics::GetPlayerController(this, 0);
	if (ACameraController* Controller = Cast<ACameraController>(FoundController))
	{
		CursorInteractor = Controller->CursorInteractor;
	}
}
