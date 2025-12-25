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

public:
	void SetMessageContent(FText NewMessage);
	void SetSlideNumber(FText NewSlideInfo);
	void SetCharacterName(FText Name);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlideNumber;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Message;

	UPROPERTY(meta = (BindWidget))
	UBorder* MessageBackdrop;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterName;

	UPROPERTY(meta = (BindWidget))
	UImage* CharacterPortrait;
};
