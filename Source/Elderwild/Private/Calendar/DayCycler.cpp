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

Seconds UDayCycler::GetTimeRemainingForTheDay()
{
	Seconds TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(DayCyclingTimerHandle);

	if (GetCurrentTimePeriod() == DAY)
	{
		TimeRemaining += NightLength;
	}
	
	return TimeRemaining;
}

FDayNight UDayCycler::GetCurrentTimePeriod()
{
	return TimePeriod;
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
