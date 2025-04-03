#include "World/Season.h"

#include "World/Day.h"


USeason::USeason()
{
	Day = CreateDefaultSubobject<UDay>("Day");
	Day->DayStateChanged.AddDynamic(this, &USeason::OnDayChange);
}

UDay* USeason::GetDayCycler()
{
	return Day;
}

int32 USeason::GetNumberOfDaysLeft()
{
	return MonthLength - CurrentDay;
}

bool USeason::IsLastDayOfMonth()
{
	return GetNumberOfDaysLeft() == 0;
}

FSeason USeason::GetSeason()
{
	return CurrentSeason;
}

void USeason::OnDayChange(FDayNight NewState)
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

FSeason USeason::GetNextSeason()
{
	int CurrentSeasonIndex = CurrentSeason;
	CurrentSeasonIndex += 1;
	CurrentSeasonIndex %= 4;

	return FSeason(CurrentSeasonIndex);
}

void USeason::ChangeSeason()
{
	CurrentSeason = GetNextSeason();
	CurrentDay = 1;
	
	SeasonIsChanging.Broadcast(CurrentSeason);

	UE_LOG(LogTemp, Log, TEXT("Season : %i is starting"), CurrentSeason);
}
