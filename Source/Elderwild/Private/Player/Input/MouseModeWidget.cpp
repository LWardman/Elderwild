#include "Player/Input/MouseModeWidget.h"

#include "Components/Button.h"
#include "Dialogue/DialogueComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Player/CameraController.h"
#include "Player/PlayerPawn.h"
#include "Player/Input/CursorInteractor.h"
#include "Player/Input/MouseModeTypes.h"


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
		CursorInteractor->ChangeMouseMode(EMouseModeType::Inspect);
	}
}

void UMouseModeWidget::OnBuildButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Build mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(EMouseModeType::Build);
	}
}

void UMouseModeWidget::OnDialogueButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Dialogue mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(EMouseModeType::Dialogue);

		APlayerController* FoundController = UGameplayStatics::GetPlayerController(this, 0);
		if (!FoundController) return;
		
		if (APlayerPawn* Player = Cast<APlayerPawn>(FoundController->GetPawn()))
		{
			if (UDialogueComponent* Dialogue = Player->DialogueComponent)
			{
				UE_LOG(LogTemp, Display, TEXT("Entering dialogue"));
				Dialogue->EnterDialogue();
			}
		}
	}
}

void UMouseModeWidget::SetCursorInteractor(UCursorInteractor* NewCursorInteractor)
{
	CursorInteractor = NewCursorInteractor;
}
