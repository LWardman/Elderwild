#include "Calendar/SeasonCycler.h"

#include "Calendar/DayCycler.h"


USeasonCycler::USeasonCycler()
{
	Day = CreateDefaultSubobject<UDayCycler>("Day");
	Day->DayStateChanged.AddDynamic(this, &USeasonCycler::OnDayChange);
}

UDayCycler* USeasonCycler::GetDayCycler()
{
	return Day;
}

int32 USeasonCycler::GetNumberOfDaysLeft()
{
	return MonthLength - CurrentDay;
}

bool USeasonCycler::IsLastDayOfMonth()
{
	return GetNumberOfDaysLeft() == 0;
}

FSeason USeasonCycler::GetSeason()
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

FSeason USeasonCycler::GetNextSeason()
{
	int CurrentSeasonIndex = CurrentSeason;
	CurrentSeasonIndex += 1;
	CurrentSeasonIndex %= 4;

	return FSeason(CurrentSeasonIndex);
}

void USeasonCycler::ChangeSeason()
{
	CurrentSeason = GetNextSeason();
	CurrentDay = 1;
	
	SeasonIsChanging.Broadcast(CurrentSeason);

	UE_LOG(LogTemp, Log, TEXT("Season : %i is starting"), CurrentSeason);
}
