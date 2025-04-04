#include "Calendar/SeasonCycler.h"
#include "Calendar/DayCycler.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCalendar, "Elderwild.Calendar", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FCalendar::RunTest(const FString& Parameters)
{
	USeasonCycler* Season = NewObject<USeasonCycler>();
	UDayCycler* Day = Season->GetDayCycler();

	TestNotNull(TEXT("Season generated properly"), Season);
	TestNotNull(TEXT("Day Cycler generated properly"), Day);
	
	Day->BeginCycling();
	
	for (int seasonNum = 0; seasonNum < 4; seasonNum++)
	{
		TestEqual(TEXT("Season is correct"), Season->GetSeason(), FSeason(seasonNum));
        
        // Get to the last day of the month
        for (int dayNum = 27; dayNum > 0; dayNum--)
        {
        	TestEqual(TEXT("GetNumberOfDaysLeft"), Season->GetNumberOfDaysLeft(), dayNum);
        
        	TestEqual(TEXT("Is Day Time"), Day->GetCurrentTimePeriod(), DAY);
            Day->ForceTransitionToNight();
            TestEqual(TEXT("Is Night Time"), Day->GetCurrentTimePeriod(), NIGHT);
            Day->ForceTransitionToDay();
        }
        
        TestEqual(TEXT("Is Last Day of Month"), Season->IsLastDayOfMonth(), true);
        
        Day->ForceTransitionToNight();
        Day->ForceTransitionToDay();
	}

	TestEqual(TEXT("Year has repeated"), Season->GetSeason(), SPRING);
	
	
	return true;
}
