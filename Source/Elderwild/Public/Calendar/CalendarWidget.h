#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarWidget.generated.h"

class UTextBlock;
class USeasonPanel;
class UTimeOfDayWidget;
enum class ESeason : uint8;

UCLASS()
class ELDERWILD_API UCalendarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateSeason(const ESeason NewSeason);
	
	UFUNCTION(BlueprintCallable)
	void UpdateDayInformation(const FString& DayInfo);
	
	UFUNCTION(BlueprintCallable)
	void UpdateTimeInformation(const float PercentThroughDay);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DayText;

	UPROPERTY(meta = (BindWidget))
	UTimeOfDayWidget* TimeWidget;

	UPROPERTY(meta = (BindWidget))
	USeasonPanel* SeasonPanel;	
};
