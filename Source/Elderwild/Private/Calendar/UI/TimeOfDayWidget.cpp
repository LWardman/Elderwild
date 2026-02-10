#include "Calendar/UI/TimeOfDayWidget.h"

#include "Components/Image.h"

void UTimeOfDayWidget::NativeConstruct()
{
	Super::NativeConstruct();	
}

void UTimeOfDayWidget::UpdateDayPercentage(float PercentThroughDay)
{
	if (!ClockBackground) return;
	
	const float NewAngle = (PercentThroughDay * 360.0f) - DegreesOffset;
	
	FWidgetTransform Transform = ClockBackground->GetRenderTransform();
	Transform.Angle = NewAngle;
	ClockBackground->SetRenderTransform(Transform);
}
