#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"

class UDialogueDisplay;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ELDERWILD_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Init(APlayerController* InController);

	void EnterDialogue();

	int32 GetNumberOfSlides() const {return Messages.Num();}
	int32 GetCurrentMessageIndex() const {return CurrentMessageIndex;}

	void MoveToNextMessage();

	void MoveToPreviousMessage();

	void ExitDialogue();

private:
	TArray<FText> Messages;

	int32 CurrentMessageIndex = 0;

	UPROPERTY()
	UDialogueDisplay* DialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UDialogueDisplay> DialogueWidgetClass;

	UPROPERTY()
	APlayerController* Controller;

	void DisplayDialogueWidget();

	FText CreateSlideNumberInformation() const;
};
