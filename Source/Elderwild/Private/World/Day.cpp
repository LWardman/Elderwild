#include "World/Day.h"

UDay::UDay()
{
	
}

void UDay::BeginDay()
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
	&UDay::EndDay, 
	NightLength, 
	false);

	NightIsStarting.Broadcast();
}

void UDay::EndDay()
{
	UE_LOG(LogTemp, Log, TEXT("Day is ending"));
}

Seconds UDay::GetTimeRemainingForTheDay()
{
	const Seconds TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(DayEndTimerHandle);
	return TimeRemaining;
}