#include "Buildings/House.h"

#include "Kismet/GameplayStatics.h"

#include "Creatures/Resident.h"

AHouse::AHouse()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHouse::BeginPlay()
{
	Super::BeginPlay();
}

void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetNumberOfInhabitants() < MaxNumberOfCreatures)
	{
		TryFillBuildingWithCreatures();
	}
}

void AHouse::TryFillBuildingWithCreatures()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreature::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (GetNumberOfInhabitants() >= MaxNumberOfCreatures) break;
		
		if (AResident* Resident = Cast<AResident>(Actor))
		{
			if (Resident->HasAHome()) continue;
			
			InhabitingCreatures.Add(Resident);
			Resident->AssignToHouse(this);
		}
	}
}