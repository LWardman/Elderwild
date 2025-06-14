#include "Gridmap/SelectionTile.h"

#include "ProceduralMeshComponent.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridVisuals.h"
#include "Gridmap/GridFactory.h"
#include "Buildings/BuildingDirection.h"
#include "Gridmap/GridDimensions.h"

USelectionTile::USelectionTile()
{
	PrimaryComponentTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for selection tile"));
}

void USelectionTile::Init(AGrid* InGrid)
{
	Grid = InGrid;

	if (!Grid)
	{
		UE_LOG(LogTemp, Warning, TEXT("Passed a null grid in to the selection tile"));
		return;
	}

	UGridFactory::GenerateSelectionSquareGeometry(Grid, ProcMesh);
	ProcMesh->SetVisibility(false);
}

void USelectionTile::SetSelectionMaterialColour(FLinearColor NewColor)
{
	if (!Grid || !Grid->GetGridVisuals())
	{
		UE_LOG(LogTemp, Warning, TEXT("Either the grid or its visuals arent initialized"));
		return;
	}
	
	SelectionMaterial = UGridVisuals::CreateMaterialInstance(NewColor, Grid->GetGridVisuals()->SelectionOpacity, Grid);

	if (ProcMesh && SelectionMaterial)
	{
		int32 NumberOfSections = 9;
		for (int32 SectionID = 0; SectionID < NumberOfSections; SectionID++)
		{
			ProcMesh->SetMaterial(SectionID, SelectionMaterial);
		}
	}
}

void USelectionTile::UpdateSelectedTile(bool IsValidTile, FVector TilePosition)
{
	if (!ProcMesh) return;
	ProcMesh->SetVisibility(true);

	SetVisibleSections({2, 3});

	ECompassDirection Direction = UBuildingDirection::GetDirection();
	float TileDirection = 180.f + static_cast<uint8>(Direction) * 90.f;
	FRotator NewTileRotation =  FRotator(0, TileDirection, 0);
	ProcMesh->SetWorldRotation(NewTileRotation);

	if (IsValidTile)
	{
		ProcMesh->SetWorldLocation(TilePosition);
	}

	FIntVector2 BaseTile = UGridDimensions::LocationToTile(TilePosition, Grid);

	CalculateRelevantTileLocations(BaseTile, {2, 3});
}

void USelectionTile::SetVisibleSections(FIntVector2 BuildingSize)
{
	if (!ProcMesh) return;
	if (!BuildingSizeIsValid(BuildingSize))
	{
		UE_LOG(LogTemp, Warning, TEXT("The building size given exceeds the maximum allowed"));
		return;
	}

	TArray<int32> RelevantSections = GetRelevantMeshSections(BuildingSize);
	
	for (int32 idx = 0; idx < MaxBuildingSize.X * MaxBuildingSize.Y; idx++)
	{
		ProcMesh->SetMeshSectionVisible(idx, RelevantSections.Contains(idx));
	}
}

bool USelectionTile::BuildingSizeIsValid(FIntVector2 BuildingSize)
{
	return (BuildingSize.X <= MaxBuildingSize.X && BuildingSize.Y <= MaxBuildingSize.Y);
}

TArray<int32> USelectionTile::GetRelevantMeshSections(FIntVector2 BuildingSize)
{
	TArray<int32> SectionsToKeep;
	
	for (int32 indX = 0; indX < BuildingSize.X; indX++)
	{
		for (int32 indY = 0; indY < BuildingSize.Y; indY++)
		{
			SectionsToKeep.Add(indY + MaxBuildingSize.X * indX);
		}
	}

	return SectionsToKeep;
}

TArray<FIntVector2> USelectionTile::CalculateRelevantTileLocations(FIntVector2 BaseTile, FIntVector2 BuildingSize)
{
	TArray<FIntVector2> RelativeTiles;

	for (int32 BuildingWidth = 0; BuildingWidth < BuildingSize.X; BuildingWidth++)
	{
		for (int32 BuildingHeight = 0; BuildingHeight < BuildingSize.Y; BuildingHeight++)
		{
			RelativeTiles.Add(FIntVector2(BuildingWidth, BuildingHeight));
		}
	}
	
	uint8 Direction = static_cast<uint8>(UBuildingDirection::GetDirection());
	TArray<FIntVector2> RelevantTiles;

	for (FIntVector2 Tile : RelativeTiles)
	{
		for (uint8 RotateCount = 0; RotateCount < Direction; RotateCount++)
		{
        	RotateRelativeTileAroundBaseBy90(Tile);
		}

		RelevantTiles.Add(BaseTile - Tile);
	}
					
	return RelevantTiles;
}		

void USelectionTile::RotateRelativeTileAroundBaseBy90(FIntVector2& Tile)
{
	int32 X = Tile.X;
	int32 Y = Tile.Y;

	Tile = FIntVector2(Y, -X);
}
