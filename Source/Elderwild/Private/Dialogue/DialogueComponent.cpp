#include "Dialogue/DialogueComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Dialogue/DialogueDisplay.h"



void UDialogueComponent::Init(APlayerController* InController)
{
	Controller = InController;

	// TODO : decouple messages from this class
	Messages.Add(FText::FromString(TEXT("blood")));
	Messages.Add(FText::FromString(TEXT("mmmmmmmmm")));
}

void UDialogueComponent::EnterDialogue()
{
	DisplayDialogueWidget();

	CurrentMessageIndex = 0;
	
	if (Messages.IsValidIndex(CurrentMessageIndex))
	{
		UGameplayStatics::SetGlobalTimeDilation(this, 0.0001f); // effectively pauses the game
		
		DialogueWidget->SetMessageContent(Messages[CurrentMessageIndex]);
		DialogueWidget->SetSlideNumber(CreateSlideNumberInformation());
	}
}

void UDialogueComponent::MoveToNextMessage()
{
	if (!DialogueWidget) return;

	CurrentMessageIndex++;

	if (Messages.IsValidIndex(CurrentMessageIndex))
	{
		DialogueWidget->SetMessageContent(Messages[CurrentMessageIndex]);
		DialogueWidget->SetSlideNumber(CreateSlideNumberInformation());
	}
	else
	{
		ExitDialogue();
	}
}

void UDialogueComponent::MoveToPreviousMessage()
{
	if (!DialogueWidget) return;

	if (Messages.IsValidIndex(CurrentMessageIndex - 1))
	{
		CurrentMessageIndex--;
		DialogueWidget->SetMessageContent(Messages[CurrentMessageIndex]);
		DialogueWidget->SetSlideNumber(CreateSlideNumberInformation());
	}
}

void UDialogueComponent::ExitDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		UGameplayStatics::SetGlobalTimeDilation(this, 1.0f); // unpauses the game
	}
}

void UDialogueComponent::DisplayDialogueWidget()
{
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("No controller to use, has this class been two step initialized?"));
		return;
	}
	if (!DialogueWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No dialogue class to use, has this property been set in the editor?"));
		return;
	}
	
	DialogueWidget = CreateWidget<UDialogueDisplay>(Controller, DialogueWidgetClass);
	if (DialogueWidget)
	{
		DialogueWidget->AddToPlayerScreen();
		UE_LOG(LogTemp, Display, TEXT("Added dialogue widget to player screen"));
	}
}

FText UDialogueComponent::CreateSlideNumberInformation() const
{
	FString CurrentNumber = FString::FromInt(CurrentMessageIndex + 1); // '+1' accounts for ints starting at 0
	FString SlideCount = FString::FromInt(GetNumberOfSlides());

	FString FormattedSlideInformation = CurrentNumber + "/" + SlideCount;
	
	return FText::FromString(FormattedSlideInformation);
}

