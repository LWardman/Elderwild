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
	}
}


void USeason::SetDayLengths()
{
	checkf(Day, TEXT("Day is not initialised"));

	// TODO : pass this information in from a TMap<int32(CurrentDay, Day-Night(struct)>
	Day->SetNewDayLengths(60.f, 60.f);
}

int32 USeason::GetNumberOfDaysLeft()
{
	return MonthLength - CurrentDay;
}

bool USeason::IsLastDayOfMonth()
{
	return GetNumberOfDaysLeft() == 0;
}