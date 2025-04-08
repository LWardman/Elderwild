#include "Calendar/Calendar.h"

#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"

#include "Calendar/DayCycler.h"
#include "Calendar/SeasonCycler.h"


UCalendar::UCalendar()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCalendar::BeginPlay()
{
	Super::BeginPlay();

	SeasonCycler = NewObject<USeasonCycler>(this);
	checkf(SeasonCycler, TEXT("Season Cycler not initialized properly"));

	UDayCycler* DayCycler = NewObject<UDayCycler>(this);
	SeasonCycler->Init(DayCycler);
	checkf(SeasonCycler->GetDayCycler(), TEXT("Season's DayCycler not initialized properly"));

	Sunlight = SearchArrayForDirectionalLight( GetActorsWithSunTag() );
}

void UCalendar::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (Sunlight)
	{
		SetSunPositionInSky();
	}
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
    	UE_LOG(LogTemp, Warning, TEXT("No directional light actor found, ensure actor has tag 'Sun' "));
    }
    else if (SunActors.Num() > 1)
    {
    	UE_LOG(LogTemp, Warning, TEXT("More than one directional light actor found"));
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
	
	float Elevation = FMath::Lerp(0.f, -40.f, FMath::Sin(PercentThroughDay * PI));
	float HorizonRotation = PercentThroughDay * 360.f;

	FRotator SunRotation = FRotator(Elevation, HorizonRotation, 0.0f);
	
	Sunlight->SetActorRotation(SunRotation);
}
