#include "Dialogue/DialogueComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Dialogue/DialogueDisplay.h"
#include "Dialogue/DialogueInformation.h"
#include "Logging/DialogueLog.h"
#include "Player/CameraController.h"

void UDialogueComponent::EnterDialogue()
{
	DisplayDialogueWidget();

	if (!DialogueInformation)
	{
		UE_LOG(DialogueLog, Warning, TEXT("No DialogueInformation found, assign a data asset"));
		return;
	}
	
	CurrentMessageIndex = 0;
	
	if (DialogueInformation->HasMessages())
	{
		UGameplayStatics::SetGlobalTimeDilation(this, 0.0001f); // effectively pauses the game
		UpdateDialogueInformation();
	}
}

void UDialogueComponent::MoveToNextMessage()
{
	if (!DialogueInformation || CurrentMessageIndex + 1 >= DialogueInformation->GetNumberOfLines())
	{
		ExitDialogue();
	}

	CurrentMessageIndex++;
	UpdateDialogueInformation();
}

void UDialogueComponent::MoveToPreviousMessage()
{
	CurrentMessageIndex--;
	CurrentMessageIndex = FMath::Max(0, CurrentMessageIndex);
	UpdateDialogueInformation();
}

void UDialogueComponent::ExitDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		UGameplayStatics::SetGlobalTimeDilation(this, 1.0f); // unpauses the game
	}
	
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (ACameraController* CameraController = Cast<ACameraController>(Controller))
	{
		CameraController->ChangeMouseMode(EMouseModeType::Inspect);
	}
}

void UDialogueComponent::UpdateDialogueInformation()
{
	if (DialogueWidget && DialogueInformation && DialogueInformation->LineNumberIsValid(CurrentMessageIndex))
	{
		DialogueWidget->SetMessageContent(GetCurrentMessage());
		DialogueWidget->SetSlideNumber(DialogueInformation->GetLineNumberText(CurrentMessageIndex));
		DialogueWidget->SetCharacterName(DialogueInformation->SpeakingCharacter);
	}	
}

FText UDialogueComponent::GetCurrentMessage()
{
	if (DialogueInformation && DialogueInformation->LineNumberIsValid(CurrentMessageIndex))
	{
		return DialogueInformation->GetLineFromNumber(CurrentMessageIndex);
	}
	return FText::GetEmpty();
}

void UDialogueComponent::DisplayDialogueWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (!Controller)
	{
		UE_LOG(DialogueLog, Error, TEXT("No controller found"));
		return;
	}
	if (!DialogueWidgetClass)
	{
		UE_LOG(DialogueLog, Error, TEXT("No dialogue class to use, has a class been set?"));
		return;
	}
	
	DialogueWidget = CreateWidget<UDialogueDisplay>(Controller, DialogueWidgetClass);
	if (DialogueWidget)
	{
		DialogueWidget->AddToPlayerScreen();
		UE_LOG(DialogueLog, Display, TEXT("Added dialogue widget to player screen"));
	}
}
