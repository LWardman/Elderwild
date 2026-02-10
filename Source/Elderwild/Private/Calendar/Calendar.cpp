#include "Calendar/Calendar.h"

#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"

#include "Calendar/DayCycler.h"
#include "Calendar/SeasonCycler.h"
#include "Calendar/CalendarWidget.h"
#include "Logging/CalendarLog.h"


UCalendar::UCalendar()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCalendar::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (CalendarWidgetClass && Controller)
	{
		CalendarWidget = CreateWidget<UCalendarWidget>(Controller, CalendarWidgetClass);
			
		if (CalendarWidget)
		{
			CalendarWidget->AddToPlayerScreen();
		}
	}
	
	SeasonCycler = NewObject<USeasonCycler>(this);
	SeasonCycler->SetMonthLength(MonthLength);
	SeasonCycler->SeasonIsChanging.AddDynamic(this, &UCalendar::SendSeasonInfoToUI);

	UDayCycler* DayCycler = NewObject<UDayCycler>(this);
	DayCycler->SetDaytimeLength(DayTimeLength);
	DayCycler->SetNightLength(NightLength);
	SeasonCycler->SetDayCycler(DayCycler);

	Sunlight = SearchArrayForDirectionalLight( GetActorsWithSunTag() );
}

void UCalendar::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (Sunlight)
	{
		SetSunPositionInSky();
	}

	SendDayInfoToUI();
	SendTimeInfoToUI();
}

EDayNight UCalendar::GetDayState()
{
	if (SeasonCycler && SeasonCycler->GetDayCycler())
	{
		return SeasonCycler->GetDayCycler()->GetCurrentTimePeriod();
	}
	return EDayNight::Day;
}

TArray<AActor*> UCalendar::GetActorsWithSunTag()
{
	TArray<AActor*> SunActors;
	UGameplayStatics::GetAllActorsWithTag(this, FName("Sun"), SunActors);
	return SunActors;
}

ADirectionalLight* UCalendar::SearchArrayForDirectionalLight(TArray<AActor*> SunActors)
{
	ADirectionalLight* DirectionalLightActor = nullptr;
    
    if (SunActors.IsEmpty())
    {
    	UE_LOG(CalendarLog, Warning, TEXT("No directional light actor found, ensure actor has tag 'Sun' "));
    }
    else if (SunActors.Num() > 1)
    {
    	UE_LOG(CalendarLog, Warning, TEXT("More than one directional light actor found"));
    	for (AActor* Actor : SunActors)
    	{
    		if (Actor->IsA(ADirectionalLight::StaticClass()))
    		{
    			DirectionalLightActor = Cast<ADirectionalLight>(Actor);
    			break;
    		}
    	}
    }
    else
    {
    	DirectionalLightActor = Cast<ADirectionalLight>(SunActors[0]);
    }
    
    return DirectionalLightActor;
}

void UCalendar::SetSunPositionInSky()
{
	if (!SeasonCycler || !SeasonCycler->GetDayCycler() || !Sunlight) return;
	
	float PercentThroughDay = SeasonCycler->GetDayCycler()->PercentWayThroughDay();
	
	float Elevation = FMath::Lerp(5.f, -55.f, FMath::Sin(PercentThroughDay * 2 * PI));
	float HorizonRotation = PercentThroughDay * 360.f;

	FRotator SunRotation = FRotator(Elevation, HorizonRotation, 0.0f);
	
	Sunlight->SetActorRotation(SunRotation);
}

void UCalendar::SendSeasonInfoToUI(ESeason NewSeason)
{
	if (CalendarWidget) CalendarWidget->UpdateSeason(NewSeason);
}

void UCalendar::SendDayInfoToUI()
{
	if (!CalendarWidget || !SeasonCycler) return;

	int32 DayNumber = SeasonCycler->GetCurrentDay();
	FString DayInfo = FString::Printf(TEXT("Current Day : %i"), DayNumber);
	CalendarWidget->UpdateDayInformation(DayInfo);
}

void UCalendar::SendTimeInfoToUI()
{
	if (!CalendarWidget || !SeasonCycler || !SeasonCycler->GetDayCycler()) return;

	const float PercentThroughDay = SeasonCycler->GetDayCycler()->PercentWayThroughDay();
	CalendarWidget->UpdateTimeInformation(PercentThroughDay);
}
