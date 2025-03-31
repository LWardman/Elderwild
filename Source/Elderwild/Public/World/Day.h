#pragma once

#include "CoreMinimal.h"
#include "Day.generated.h"

typedef float Seconds;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDayToNightDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNightToDayDelegate);


// TODO : Can a blueprint of this be made and put into the world? How will this work?
UCLASS()
class ELDERWILD_API UDay : public UObject
{
	GENERATED_BODY()

	UDay();

protected:
	// TODO : begin play is not valid in a UObject, find an alternative
	virtual void BeginPlay() override;

private:
	void BeginDay();
	void TransitionToNight();
	void EndDay();

	Seconds DaytimeLength = 60.f;
	Seconds NightLength = 60.f;
	Seconds FullDayCycle = DaytimeLength + NightLength;

	FTimerHandle DayEndTimerHandle;

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FNightToDayDelegate DayIsStarting;
	
	UPROPERTY(BlueprintAssignable, Category = "Test")
	FDayToNightDelegate NightIsStarting;

	Seconds GetTimeRemainingForTheDay();
};
