#include "Calendar/DayCycler.h"


void UDayCycler::BeginCycling()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			DayCyclingTimerHandle, 
			this, 
			&UDayCycler::TransitionToNight, 
			DaytimeLength, 
			false);
	}
}

void UDayCycler::ForceTransitionToDay()
{
	TransitionToDay();
}

void UDayCycler::ForceTransitionToNight()
{
	TransitionToNight();
}

float UDayCycler::PercentWayThroughDay() const
{
	return (1 - GetTimeRemainingForTheDay() / FullDayCycle);
}

EDayNight UDayCycler::GetCurrentTimePeriod() const
{
	return TimePeriod;
}

Seconds UDayCycler::GetTimeRemainingForTheDay() const
{
	if (!GetWorld()) return FullDayCycle;
	
	Seconds TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(DayCyclingTimerHandle);

	if (GetCurrentTimePeriod() == EDayNight::Day)
	{
		TimeRemaining += NightLength;
	}
	
	return TimeRemaining;
}

void UDayCycler::TransitionToDay()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
        	DayCyclingTimerHandle, 
        	this, 
        	&UDayCycler::TransitionToNight, 
        	DaytimeLength, 
        	false);
	}
	
	TimePeriod = EDayNight::Day;
	DayStateChanged.Broadcast(GetCurrentTimePeriod());
}

void UDayCycler::TransitionToNight()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
        	DayCyclingTimerHandle, 
        	this, 
        	&UDayCycler::TransitionToDay, 
        	NightLength, 
        	false);
	}

	TimePeriod = EDayNight::Night;
	DayStateChanged.Broadcast(GetCurrentTimePeriod());
}
