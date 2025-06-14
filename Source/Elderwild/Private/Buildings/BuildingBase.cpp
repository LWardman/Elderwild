#include "Buildings/BuildingBase.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"
#include "GameModes/DevGameMode.h"

ABuildingBase::ABuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();

	FindEntranceLocation();
	SpawnDebugSphereAtEntrance();
}

void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 ABuildingBase::GetNumberOfInhabitants() const
{
	return InhabitingCreatures.Num();
}

void ABuildingBase::SetBuildingSize(FIntVector2 NewBuildingSize)
{
	if (NewBuildingSize.X > 0 && NewBuildingSize.Y > 0)
	{
		BuildingSize = NewBuildingSize;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("An invalid size has been assigned to a building, defaulting to (1,1)"));
		BuildingSize = FIntVector2(1, 1);
	}
}

void ABuildingBase::FindEntranceLocation()
{
	FVector CurrentLocation = GetActorLocation();

	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	
	AGrid* Grid = GameMode->GetGrid();
	if (!Grid || !Grid->GetGridDimensions()) return;

	int32 TileSize = Grid->GetGridDimensions()->GetTileSize();
	int32 HalfTileLength = TileSize / 2;

	FVector ForwardVec = GetActorForwardVector();

	EntranceLocation = CurrentLocation + ForwardVec * HalfTileLength;
}

void ABuildingBase::SpawnDebugSphereAtEntrance() const
{
	DrawDebugSphere(GetWorld(), EntranceLocation, 12, 10, FColor::Red, true);
}

