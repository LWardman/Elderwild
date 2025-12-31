#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"

class UDialogueDisplay;
class UDialogueInformation;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ELDERWILD_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void EnterDialogue();
	void MoveToNextMessage();
	void MoveToPreviousMessage();
	void ExitDialogue();

private:
	UDialogueInformation* DialogueInformation;
	int32 CurrentMessageIndex = 0;
	void UpdateDialogueInformation();
	FText GetCurrentMessage();
	void DisplayDialogueWidget();

	UPROPERTY()
	UDialogueDisplay* DialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess))
	TSubclassOf<UDialogueDisplay> DialogueWidgetClass;
};
