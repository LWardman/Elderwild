#include "World/Season.h"

#include "World/Day.h"

USeason::USeason()
{
	Day = CreateDefaultSubobject<UDay>("Day");
	Day->DayIsStarting.AddDynamic(this, &USeason::OnDayChange);
}

void USeason::OnDayChange()
{
	if (IsLastDayOfMonth())
	{
		SeasonIsChanging.Broadcast();
		CurrentSeason = GetNextSeason();

		UE_LOG(LogTemp, Log, TEXT("Season : %i is starting"), CurrentSeason);
	}
}

FSeason USeason::GetNextSeason()
{
	int CurrentSeasonIndex = CurrentSeason;
	CurrentSeasonIndex += 1;
	CurrentSeasonIndex %= 4;

	return FSeason(CurrentSeasonIndex);
}

int32 USeason::GetNumberOfDaysLeft()
{
	return MonthLength - CurrentDay;
}

bool USeason::IsLastDayOfMonth()
{
	return GetNumberOfDaysLeft() == 0;
}