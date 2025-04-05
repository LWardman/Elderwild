#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DayCycler.generated.h"

UENUM(BlueprintType)
enum FDayNight : int { DAY, NIGHT };

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayStateChanged, FDayNight, NewState);

typedef float Seconds;

UCLASS()
class ELDERWILD_API UDayCycler : public UObject
{
	GENERATED_BODY()

public:
	void BeginCycling();

	void ForceTransitionToDay();
	void ForceTransitionToNight();

	UPROPERTY(BlueprintAssignable, Category = "Day Events")
	FDayStateChanged DayStateChanged;

	float PercentWayThroughDay() const;

	FDayNight GetCurrentTimePeriod() const;
	
private:
	FTimerHandle DayCyclingTimerHandle;

	Seconds GetTimeRemainingForTheDay() const;
	
	Seconds DaytimeLength = 60.f;
	Seconds NightLength = 60.f;
	Seconds FullDayCycle = DaytimeLength + NightLength;

	FDayNight TimePeriod = DAY;
	
	void TransitionToDay();
	void TransitionToNight();
};
