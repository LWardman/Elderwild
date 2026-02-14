#include "Buildings/House.h"

#include "Buildings/Components/EntranceLocationComponent.h"
#include "Buildings/Components/InhabitanceComponent.h"

AHouse::AHouse()
{
	PrimaryActorTick.bCanEverTick = true;
	
	InhabitanceComponent = CreateDefaultSubobject<UInhabitanceComponent>(TEXT("Inhabitance Component"));
	InhabitanceComponent->SetShouldAutomaticallyPopulate(true);
	
	EntranceLocationComponent = CreateDefaultSubobject<UEntranceLocationComponent>(TEXT("Entrance Location Component"));
	
	EntranceLocationComponent->SetupAttachment(RootComponent);
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();
	
	if (EntranceLocationComponent)
	{
		EntranceLocationComponent->Init(GetBuildingSize());
	}
}

void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
