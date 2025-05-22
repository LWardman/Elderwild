#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MouseModeWidget.generated.h"

class UButton;
class UCursorInteractor;
class UMouseMode;

/* This is a debug class and shouldnt be used in the finished product
 */
UCLASS()
class ELDERWILD_API UMouseModeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION()
	void OnInspectButtonPressed();

	UFUNCTION()
	void OnBuildButtonPressed();

	UFUNCTION()
	void OnDialogueButtonPressed();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* InspectButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BuildButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DialogueButton;

private:
	UPROPERTY()
	UCursorInteractor* CursorInteractor;

	void SetCursorInteractor();

	UPROPERTY(EditAnywhere, Category="Mouse Modes", meta=(AllowPrivateAccess))
	TSubclassOf<UMouseMode> InspectModeClass;

	UPROPERTY(EditAnywhere, Category="Mouse Modes", meta=(AllowPrivateAccess))
	TSubclassOf<UMouseMode> BuildModeClass;

	UPROPERTY(EditAnywhere, Category="Mouse Modes", meta=(AllowPrivateAccess))
	TSubclassOf<UMouseMode> DialogueModeClass;
};
