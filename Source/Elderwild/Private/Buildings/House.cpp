#include "Buildings/House.h"

#include "Buildings/Components/InhabitanceComponent.h"

AHouse::AHouse()
{
	PrimaryActorTick.bCanEverTick = true;
	
	InhabitanceComponent = CreateDefaultSubobject<UInhabitanceComponent>(TEXT("Inhabitance Component"));
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();
}

void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
