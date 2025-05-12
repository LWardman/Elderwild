#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DayCycler.generated.h"

UENUM(BlueprintType)
enum class EDayNight : uint8
{
	Day,
	Night
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayStateChanged, EDayNight, NewState);

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

	EDayNight GetCurrentTimePeriod() const;
	
private:
	FTimerHandle DayCyclingTimerHandle;

	Seconds GetTimeRemainingForTheDay() const;
	
	Seconds DaytimeLength = 5.f;
	Seconds NightLength = 5.f;
	Seconds FullDayCycle = DaytimeLength + NightLength;

	EDayNight TimePeriod = EDayNight::Day;
	
	void TransitionToDay();
	void TransitionToNight();
};
