#include "Buildings/Components/EntranceLocationComponent.h"

#include "Kismet/GameplayStatics.h"

#include "GameModes/DevGameMode.h"
#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"

void UEntranceLocationComponent::Init(FIntVector2 BuildingSize)
{
	SetEntranceLocation(BuildingSize);
	SpawnDebugSphereAtEntrance();
}

void UEntranceLocationComponent::SetEntranceLocation(FIntVector2 BuildingSize)
{
	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	
	AGrid* Grid = GameMode->GetGrid();
	if (!Grid || !Grid->GetGridDimensions()) return;
	
	int32 TileSize = Grid->GetGridDimensions()->GetTileSize();
	int32 HalfTileLength = TileSize / 2;
	int32 BuildingDepth = BuildingSize.Y;
	
	FVector EntranceOffset = GetComponentLocation() + GetForwardVector() * HalfTileLength * BuildingDepth;
	SetWorldLocation(EntranceOffset);
}

void UEntranceLocationComponent::SpawnDebugSphereAtEntrance() const
{
	DrawDebugSphere(GetWorld(), GetComponentLocation(), 12, 10, FColor::Red, true);
}
