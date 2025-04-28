#include "Player/BuildingModeWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "Player/CameraController.h"
#include "Player/CursorInteractor.h"


void UBuildingModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DefaultButton)
	{
		DefaultButton->OnReleased.AddDynamic(this, &UBuildingModeWidget::OnDefaultButtonPressed);
	}
	if (BuildButton)
	{
		BuildButton->OnReleased.AddDynamic(this, &UBuildingModeWidget::OnBuildButtonPressed);
	}

	SetCursorInteractor();
}

void UBuildingModeWidget::OnDefaultButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Default mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(FMouseMode::DEFAULT);
	}
}

void UBuildingModeWidget::OnBuildButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Build mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(FMouseMode::BUILDING);
	}
}

void UBuildingModeWidget::SetCursorInteractor()
{
	// Is this a valid world context object?
	APlayerController* FoundController = UGameplayStatics::GetPlayerController(this, 0);
	if (ACameraController* Controller = Cast<ACameraController>(FoundController))
	{
		CursorInteractor = Controller->CursorInteractor;
	}
}
