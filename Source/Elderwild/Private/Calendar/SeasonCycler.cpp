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

	SeasonIsChanging.Broadcast(CurrentSeason);
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

ESeason USeasonCycler::GetSeason() const
{
	return CurrentSeason;
}

void USeasonCycler::OnDayChange(EDayNight NewState)
{
	if (NewState == EDayNight::Day)
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

ESeason USeasonCycler::GetNextSeason() const 
{
	int32 SeasonValue = static_cast<int32>(CurrentSeason);
	SeasonValue = (SeasonValue + 1) % 4;
	return static_cast<ESeason>(SeasonValue);
}

void USeasonCycler::ChangeSeason()
{
	CurrentSeason = GetNextSeason();
	CurrentDay = 1;
	
	SeasonIsChanging.Broadcast(CurrentSeason);

	UE_LOG(LogTemp, Log, TEXT("Season : %i is starting"), CurrentSeason);
}
