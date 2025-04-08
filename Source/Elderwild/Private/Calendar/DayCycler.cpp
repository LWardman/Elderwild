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

FDayNight UDayCycler::GetCurrentTimePeriod() const
{
	return TimePeriod;
}

Seconds UDayCycler::GetTimeRemainingForTheDay() const
{
	if (!GetWorld()) return FullDayCycle;
	
	Seconds TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(DayCyclingTimerHandle);

	if (GetCurrentTimePeriod() == DAY)
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
	
	TimePeriod = DAY;
	DayStateChanged.Broadcast(GetCurrentTimePeriod());

	UE_LOG(LogTemp, Log, TEXT("Day Time"));
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

	TimePeriod = NIGHT;
	DayStateChanged.Broadcast(GetCurrentTimePeriod());
	
	UE_LOG(LogTemp, Log, TEXT("Night Time"));
}
// TODO : These logs arent showing up, why?