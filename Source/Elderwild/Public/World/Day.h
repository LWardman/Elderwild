#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Day.generated.h"

typedef float Seconds;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNightStartsDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDayStartsDelegate);


UCLASS()
class ELDERWILD_API UDay : public UObject
{
	GENERATED_BODY()

public:
	UDay();

	void BeginCycling();

	void SetNewDayLengths(Seconds NewDayLength, Seconds NewNightLength);
	
	UPROPERTY(BlueprintAssignable, Category = "Day Events")
	FDayStartsDelegate DayIsStarting;
	
	UPROPERTY(BlueprintAssignable, Category = "Day Events")
	FNightStartsDelegate NightIsStarting;
	
private:
	FTimerHandle DayEndTimerHandle;
	
	Seconds DaytimeLength = 60.f;
	Seconds NightLength = 60.f;
	Seconds FullDayCycle = DaytimeLength + NightLength;
	
	void TransitionToDay();
	void TransitionToNight();

	Seconds GetTimeRemainingForTheDay();
};
