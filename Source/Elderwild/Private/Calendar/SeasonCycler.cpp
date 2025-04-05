#include "Calendar/SeasonCycler.h"

#include "Calendar/DayCycler.h"


void USeasonCycler::Init(UDayCycler* DayCycler)
{
	Day = DayCycler;
	if (Day)
	{
		Day->BeginCycling();
		Day->DayStateChanged.AddDynamic(this, &USeasonCycler::OnDayChange);
	}
}

UDayCycler* USeasonCycler::GetDayCycler() const
{
	return Day;
}

int32 USeasonCycler::GetNumberOfDaysLeft() const
{
	return MonthLength - CurrentDay;
}

bool USeasonCycler::IsLastDayOfMonth() const
{
	return GetNumberOfDaysLeft() == 0;
}

FSeason USeasonCycler::GetSeason() const
{
	return CurrentSeason;
}

void USeasonCycler::OnDayChange(FDayNight NewState)
{
	if (NewState == DAY)
	{
		if (IsLastDayOfMonth())
		{
			ChangeSeason();
		}
		else
		{
			CurrentDay++;
		}
	}
}

FSeason USeasonCycler::GetNextSeason() const 
{
	int CurrentSeasonIndex = CurrentSeason;
	CurrentSeasonIndex += 1;
	CurrentSeasonIndex %= 4;
	
	return StaticCast<FSeason>(CurrentSeasonIndex);
}

void USeasonCycler::ChangeSeason()
{
	CurrentSeason = GetNextSeason();
	CurrentDay = 1;
	
	SeasonIsChanging.Broadcast(CurrentSeason);

	UE_LOG(LogTemp, Log, TEXT("Season : %i is starting"), CurrentSeason);
}
