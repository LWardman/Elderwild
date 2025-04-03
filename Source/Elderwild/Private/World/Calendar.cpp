#include "World/Calendar.h"

UCalendar::UCalendar()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCalendar::BeginPlay()
{
	Super::BeginPlay();
}

void UCalendar::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

