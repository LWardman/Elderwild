#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarWidget.generated.h"

class UTextBlock;

// TODO : hook this up in the calendar class
UCLASS()
class ELDERWILD_API UCalendarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateCalendarDisplay(const FString& Day, const FString& TimeOfDay, const FString& Season);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DayText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SeasonText;
};
