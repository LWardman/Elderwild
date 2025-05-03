#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MouseModeWidget.generated.h"

class UButton;
class UCursorInteractor;

UCLASS()
class ELDERWILD_API UMouseModeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION()
	void OnDefaultButtonPressed();

	UFUNCTION()
	void OnBuildButtonPressed();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* DefaultButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BuildButton;

private:
	UPROPERTY()
	UCursorInteractor* CursorInteractor;

	void SetCursorInteractor();
};
