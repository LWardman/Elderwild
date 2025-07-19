#include "Buildings/House.h"

#include "Kismet/GameplayStatics.h"

#include "Creatures/CreatureBase.h"

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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreatureBase::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (GetNumberOfInhabitants() >= MaxNumberOfCreatures) break;
		
		if (ACreatureBase* Creature = Cast<ACreatureBase>(Actor))
		{
			if (Creature->HasAHome()) continue;
			
			InhabitingCreatures.Add(Creature);
			Creature->AssignToHouse(this);
		}
	}
}