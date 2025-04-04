#include "Calendar/Calendar.h"

#include "Calendar/DayCycler.h"
#include "Calendar/SeasonCycler.h"
#include "Kismet/GameplayStatics.h"

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

	TArray<AActor*> SunActors;
	UGameplayStatics::GetAllActorsWithTag(this, "Sun", SunActors);
	
	UE_LOG(LogTemp, Display, TEXT("Found %i sun actors"), SunActors.Num());
}
