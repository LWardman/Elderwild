#include "World/Day.h"

UDay::UDay()
{
	
}

void UDay::BeginCycling()
{
	TransitionToDay();
}

void UDay::SetNewDayLengths(Seconds NewDayLength, Seconds NewNightLength)
{
	DaytimeLength = NewDayLength;
	NightLength = NewNightLength;
	FullDayCycle = DaytimeLength + NightLength;
}

void UDay::TransitionToDay()
{
	GetWorld()->GetTimerManager().SetTimer(
	DayEndTimerHandle, 
	this, 
	&UDay::TransitionToNight, 
	DaytimeLength, 
	false);

	DayIsStarting.Broadcast();
}

void UDay::TransitionToNight()
{
	GetWorld()->GetTimerManager().SetTimer(
	DayEndTimerHandle, 
	this, 
	&UDay::TransitionToDay, 
	NightLength, 
	false);

	NightIsStarting.Broadcast();
}

Seconds UDay::GetTimeRemainingForTheDay()
{
	const Seconds TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(DayEndTimerHandle);
	return TimeRemaining;
}