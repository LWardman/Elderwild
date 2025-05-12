#include "Buildings/BuildingBase.h"

ABuildingBase::ABuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 ABuildingBase::GetNumberOfInhabitants()
{
	return InhabitingCreatures.Num();
}
