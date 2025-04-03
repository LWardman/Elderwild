#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Day.generated.h"

typedef float Seconds;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNightStartsDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDayStartsDelegate);

// TODO : create link between this and the suns position in the engine.
UCLASS()
class ELDERWILD_API UDay : public UObject
{
	GENERATED_BODY()

public:
	// TODO : Call this where appropriate
	void BeginCycling();
	
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
