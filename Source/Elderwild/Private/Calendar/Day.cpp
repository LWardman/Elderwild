#include "World/Day.h"


void UDay::BeginCycling()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			DayCyclingTimerHandle, 
			this, 
			&UDay::TransitionToNight, 
			DaytimeLength, 
			false);
	}
}

void UDay::ForceTransitionToDay()
{
	TransitionToDay();
}

void UDay::ForceTransitionToNight()
{
	TransitionToNight();
}

Seconds UDay::GetTimeRemainingForTheDay()
{
	Seconds TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(DayCyclingTimerHandle);

	if (GetCurrentTimePeriod() == DAY)
	{
		TimeRemaining += NightLength;
	}
	
	return TimeRemaining;
}

FDayNight UDay::GetCurrentTimePeriod()
{
	return TimePeriod;
}

void UDay::TransitionToDay()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
        	DayCyclingTimerHandle, 
        	this, 
        	&UDay::TransitionToNight, 
        	DaytimeLength, 
        	false);
	}
	
	TimePeriod = DAY;
	DayStateChanged.Broadcast(GetCurrentTimePeriod());

	UE_LOG(LogTemp, Log, TEXT("Day Time"));
}

void UDay::TransitionToNight()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
        	DayCyclingTimerHandle, 
        	this, 
        	&UDay::TransitionToDay, 
        	NightLength, 
        	false);
	}

	TimePeriod = NIGHT;
	DayStateChanged.Broadcast(GetCurrentTimePeriod());
	
	UE_LOG(LogTemp, Log, TEXT("Night Time"));
}
