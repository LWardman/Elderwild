#include "World/Day.h"


void UDay::BeginCycling()
{
	TransitionToDay();
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

	UE_LOG(LogTemp, Log, TEXT("Day Time"));
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
	
	UE_LOG(LogTemp, Log, TEXT("Night Time"));
}

Seconds UDay::GetTimeRemainingForTheDay()
{
	const Seconds TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(DayEndTimerHandle);
	return TimeRemaining;
}