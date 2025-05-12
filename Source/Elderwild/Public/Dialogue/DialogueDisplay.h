#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueDisplay.generated.h"

class UTextBlock;
class UImage;
class UBorder;

UCLASS()
class ELDERWILD_API UDialogueDisplay : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Message;

	UPROPERTY(meta = (BindWidget))
	UBorder* MessageBackdrop;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpeakingCharacterName;

	UPROPERTY(meta = (BindWidget))
	UImage* SpeakingCharacter;
};
