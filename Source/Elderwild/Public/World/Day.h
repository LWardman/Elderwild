#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Day.generated.h"

typedef float Seconds;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDayToNightDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNightToDayDelegate);


UCLASS()
class ELDERWILD_API UDay : public UObject
{
	GENERATED_BODY()

public:
	UDay();

	void BeginCycling();

	void SetNewDayLengths(Seconds NewDayLength, Seconds NewNightLength);

private:
	Seconds DaytimeLength = 60.f;
	Seconds NightLength = 60.f;
	Seconds FullDayCycle = DaytimeLength + NightLength;
	
	void TransitionToDay();
	void TransitionToNight();

	FTimerHandle DayEndTimerHandle;

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FNightToDayDelegate DayIsStarting;
	
	UPROPERTY(BlueprintAssignable, Category = "Test")
	FDayToNightDelegate NightIsStarting;

	Seconds GetTimeRemainingForTheDay();
};
