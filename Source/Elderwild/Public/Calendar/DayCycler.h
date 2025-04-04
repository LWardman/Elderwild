#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DayCycler.generated.h"


UENUM(BlueprintType)
enum FDayNight
{
	DAY,
	NIGHT
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNightStartsDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDayStartsDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayStateChanged, FDayNight, NewState);

typedef float Seconds;

// TODO : create link between this and the suns position in the engine.
UCLASS()
class ELDERWILD_API UDayCycler : public UObject
{
	GENERATED_BODY()

public:
	// TODO : Call this where appropriate
	void BeginCycling();

	void ForceTransitionToDay();
	void ForceTransitionToNight();

	UPROPERTY(BlueprintAssignable, Category = "Day Events")
	FDayStateChanged DayStateChanged;

	Seconds GetTimeRemainingForTheDay();

	FDayNight GetCurrentTimePeriod();
	
private:
	FTimerHandle DayCyclingTimerHandle;
	
	Seconds DaytimeLength = 60.f;
	Seconds NightLength = 60.f;
	Seconds FullDayCycle = DaytimeLength + NightLength;

	FDayNight TimePeriod = DAY;
	
	void TransitionToDay();
	void TransitionToNight();
};
