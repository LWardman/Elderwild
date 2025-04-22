#include "Calendar/CalendarWidget.h"

#include "Components/TextBlock.h"

void UCalendarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCalendarWidget::UpdateCalendarDisplay(const FString& Day, const FString& TimeOfDay, const FString& Season)
{
	if (DayText) DayText->SetText(FText::FromString(Day));
	if (TimeText) TimeText->SetText(FText::FromString(TimeOfDay));
	if (SeasonText) SeasonText->SetText(FText::FromString(Season));
}