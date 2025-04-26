#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarWidget.generated.h"

class UTextBlock;

UCLASS()
class ELDERWILD_API UCalendarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateSeasonInformation(const FString& SeasonInfo);
	
	UFUNCTION(BlueprintCallable)
	void UpdateDayInformation(const FString& DayInfo);
	
	UFUNCTION(BlueprintCallable)
	void UpdateTimeInformation(const FString& TimeInfo);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DayText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SeasonText;
};
