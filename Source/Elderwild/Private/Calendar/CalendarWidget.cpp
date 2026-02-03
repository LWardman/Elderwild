#include "Calendar/CalendarWidget.h"

#include "Calendar/UI/SeasonPanel.h"
#include "Components/TextBlock.h"


void UCalendarWidget::UpdateSeason(const ESeason NewSeason)
{
	if (SeasonPanel) SeasonPanel->UpdateSeason(NewSeason);
}

void UCalendarWidget::UpdateDayInformation(const FString& DayInfo)
{
	if (DayText) DayText->SetText(FText::FromString(DayInfo));
}

void UCalendarWidget::UpdateTimeInformation(const FString& TimeInfo)
{
	if (TimeText) TimeText->SetText(FText::FromString(TimeInfo));
}
