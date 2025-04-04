#include "Calendar/Calendar.h"

#include "Calendar/DayCycler.h"
#include "Calendar/SeasonCycler.h"

UCalendar::UCalendar()
{
	PrimaryComponentTick.bCanEverTick = true;

	SeasonCycler = CreateDefaultSubobject<USeasonCycler>("SeasonCycler");
}

void UCalendar::BeginPlay()
{
	Super::BeginPlay();

	checkf(SeasonCycler, TEXT("Season Cycler not initialized properly"));
	checkf(SeasonCycler->GetDayCycler(), TEXT("Season's DayCycler not initialized properly"));

	SeasonCycler->GetDayCycler()->BeginCycling();
}
