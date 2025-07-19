#include "Buildings/Building.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"
#include "GameModes/DevGameMode.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	FindEntranceLocation();
	SpawnDebugSphereAtEntrance();
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 ABuilding::GetNumberOfInhabitants() const
{
	return InhabitingCreatures.Num();
}

void ABuilding::SetBuildingSize(FIntVector2 NewBuildingSize)
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

void ABuilding::FindEntranceLocation()
{
	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this));
	
	if (!GameMode) return;
	
	AGrid* Grid = GameMode->GetGrid();
	if (!Grid || !Grid->GetGridDimensions()) return;

	int32 TileSize = Grid->GetGridDimensions()->GetTileSize();
	int32 HalfTileLength = TileSize / 2;
	int32 BuildingDepth = BuildingSize.Y;
	
	FVector ForwardVec = GetActorForwardVector();

	EntranceLocation = GetActorLocation() + ForwardVec * HalfTileLength * BuildingDepth;
}

void ABuilding::SpawnDebugSphereAtEntrance() const
{
	DrawDebugSphere(GetWorld(), EntranceLocation, 12, 10, FColor::Red, true);
}

