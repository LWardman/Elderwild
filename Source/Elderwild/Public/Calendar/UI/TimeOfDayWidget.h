#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeOfDayWidget.generated.h"

class UImage;

/**
 *   Displays a clock hand pointing to the time of day
 */
UCLASS()
class ELDERWILD_API UTimeOfDayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	void UpdateDayPercentage(float PercentThroughDay);
	
protected:
	UPROPERTY(meta=(BindWidget))
	UImage* ClockHand;
	
	UPROPERTY(meta=(BindWidget))
	UImage* ClockBackground;
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Clock")
	float DegreesOffset = 0.0f;
};
