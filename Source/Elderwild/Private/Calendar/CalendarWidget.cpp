#include "Calendar/CalendarWidget.h"

#include "Components/TextBlock.h"


void UCalendarWidget::UpdateSeasonInformation(const FString& SeasonInfo)
{
	if (SeasonText) SeasonText->SetText(FText::FromString(SeasonInfo));
}

void UCalendarWidget::UpdateDayInformation(const FString& DayInfo)
{
	if (DayText) DayText->SetText(FText::FromString(DayInfo));
}

void UCalendarWidget::UpdateTimeInformation(const FString& TimeInfo)
{
	if (TimeText) TimeText->SetText(FText::FromString(TimeInfo));
}
