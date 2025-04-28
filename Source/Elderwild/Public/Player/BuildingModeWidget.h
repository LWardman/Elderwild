#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingModeWidget.generated.h"

class UButton;

class UCursorInteractor;

// TODO : rename to UMouseModeWidget
UCLASS()
class ELDERWILD_API UBuildingModeWidget : public UUserWidget
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
