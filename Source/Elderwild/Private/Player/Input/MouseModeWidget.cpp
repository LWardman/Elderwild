#include "Player/Input/MouseModeWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "Player/CameraController.h"
#include "Player/Input/CursorInteractor.h"


void UMouseModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InspectButton)
	{
		InspectButton->OnReleased.AddDynamic(this, &UMouseModeWidget::OnInspectButtonPressed);
	}
	if (BuildButton)
	{
		BuildButton->OnReleased.AddDynamic(this, &UMouseModeWidget::OnBuildButtonPressed);
	}
	if (DialogueButton)
	{
		DialogueButton->OnReleased.AddDynamic(this, &UMouseModeWidget::OnDialogueButtonPressed);
	}

	SetCursorInteractor();
}

void UMouseModeWidget::OnInspectButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Inspect mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(InspectModeClass);
	}
}

void UMouseModeWidget::OnBuildButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Build mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(BuildModeClass);
	}
}

void UMouseModeWidget::OnDialogueButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Dialogue mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(DialogueModeClass);
	}
}

// TODO : Can't CursorInteractor just be passed in since it owns this?
void UMouseModeWidget::SetCursorInteractor()
{
	APlayerController* FoundController = UGameplayStatics::GetPlayerController(this, 0);
	if (ACameraController* Controller = Cast<ACameraController>(FoundController))
	{
		CursorInteractor = Controller->CursorInteractor;
	}
}
