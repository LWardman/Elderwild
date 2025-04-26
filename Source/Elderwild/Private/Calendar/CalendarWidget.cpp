#include "Calendar/CalendarWidget.h"

#include "Components/TextBlock.h"

void UCalendarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCalendarWidget::UpdateSeasonInformation(const FString& SeasonInfo)
{
	UE_LOG(LogTemp, Display, TEXT("Updating Season Text"));
	if (SeasonText) SeasonText->SetText(FText::FromString(SeasonInfo));
}

void UCalendarWidget::UpdateDayInformation(const FString& DayInfo)
{
	UE_LOG(LogTemp, Display, TEXT("Updating Day Text"));
	if (DayText) DayText->SetText(FText::FromString(DayInfo));
}

void UCalendarWidget::UpdateTimeInformation(const FString& TimeInfo)
{
	UE_LOG(LogTemp, Display, TEXT("Updating Time Text"));
	if (TimeText) TimeText->SetText(FText::FromString(TimeInfo));
}
