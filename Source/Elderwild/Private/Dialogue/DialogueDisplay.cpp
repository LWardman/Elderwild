#include "Dialogue/DialogueDisplay.h"

#include "Components/TextBlock.h"

void UDialogueDisplay::SetMessageContent(FText NewMessage)
{
	if (Message) Message->SetText(NewMessage);
}

void UDialogueDisplay::SetSlideNumber(FText NewSlideInfo)
{
	if (SlideNumber) SlideNumber->SetText(NewSlideInfo);
}

void UDialogueDisplay::SetCharacterName(FText Name)
{
	if (CharacterName) CharacterName->SetText(Name);
}