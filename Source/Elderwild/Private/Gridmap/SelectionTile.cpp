#include "Gridmap/SelectionTile.h"

#include "ProceduralMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridVisuals.h"
#include "Gridmap/GridFactory.h"
#include "Buildings/BuildingDirection.h"
#include "Gridmap/GridDimensions.h"
#include "Logging/GridLog.h"
#include "Gridmap/UI/BuildingSizeSelector.h"

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
		UE_LOG(GridLog, Warning, TEXT("Passed a null grid in to the selection tile"));
		return;
	}

	UGridFactory::GenerateSelectionSquareGeometry(Grid, ProcMesh);
	ProcMesh->SetVisibility(false);
}

void USelectionTile::BeginPlay()
{
	Super::BeginPlay();
	
	CreateBuildingSizeSelectorWidget();
}

void USelectionTile::SetSelectionMaterialColour(FLinearColor NewColor)
{
	if (!Grid || !Grid->GetGridVisuals())
	{
		UE_LOG(GridLog, Warning, TEXT("Either the grid or its visuals arent initialized"));
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
	ProcMesh->SetVisibility(IsValidTile);

	SetVisibleSections();

	ECompassDirection Direction = UBuildingDirection::GetDirection();
	float TileDirection = 180.f + static_cast<uint8>(Direction) * 90.f;
	FRotator NewTileRotation =  FRotator(0, TileDirection, 0);
	ProcMesh->SetWorldRotation(NewTileRotation);

	if (IsValidTile)
	{
		ProcMesh->SetWorldLocation(TilePosition);
	}

	FIntVector2 BaseTile = UGridDimensions::LocationToTile(TilePosition, Grid);

	CalculateRelevantTileLocations(BaseTile);
}

void USelectionTile::SetVisibleSections()
{
	if (!ProcMesh) return;
	if (!BuildingSizeIsValid())
	{
		UE_LOG(GridLog, Warning, TEXT("The building size given exceeds the maximum allowed"));
		return;
	}

	TArray<int32> RelevantSections = GetRelevantMeshSections();
	
	for (int32 idx = 0; idx < MaxBuildingSize.X * MaxBuildingSize.Y; idx++)
	{
		ProcMesh->SetMeshSectionVisible(idx, RelevantSections.Contains(idx));
	}
}

bool USelectionTile::BuildingSizeIsValid()
{
	return (BuildingSize.X <= MaxBuildingSize.X && BuildingSize.Y <= MaxBuildingSize.Y);
}

TArray<int32> USelectionTile::GetRelevantMeshSections()
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

TArray<FIntVector2> USelectionTile::CalculateRelevantTileLocations(FIntVector2 BaseTile)
{
	TArray<FIntVector2> RelativeTiles;

	for (int32 BuildingWidth = 0; BuildingWidth < BuildingSize.Y; BuildingWidth++)
	{
		for (int32 BuildingHeight = 0; BuildingHeight < BuildingSize.X; BuildingHeight++)
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

	//LogRelevantTiles(RelevantTiles);

	return RelevantTiles;
}		

void USelectionTile::RotateRelativeTileAroundBaseBy90(FIntVector2& Tile)
{
	int32 X = Tile.X;
	int32 Y = Tile.Y;

	Tile.X = -Y;
	Tile.Y = X;
}
void USelectionTile::LogRelevantTiles(TArray<FIntVector2> Tiles)
{
	UE_LOG(GridLog, Display, TEXT("=========="));
	for (FIntVector2 Tile : Tiles)
	{
		UE_LOG(GridLog, Display, TEXT("Found Tile : %s"), *Tile.ToString());
	}
	UE_LOG(GridLog, Display, TEXT("=========="));
}

void USelectionTile::CreateBuildingSizeSelectorWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (Controller && BuildingSizeSelectorClass)
	{
		BuildingSizeSelectorWidget = CreateWidget<UBuildingSizeSelector>(Controller, BuildingSizeSelectorClass);
		
		if (BuildingSizeSelectorWidget)
		{
			BuildingSizeSelectorWidget->OnBuildingSizeSelected.AddUObject(this, &USelectionTile::OnBuildingSizeWidgetButtonClicked);
			BuildingSizeSelectorWidget->AddToPlayerScreen();
		}
	}
}

void USelectionTile::OnBuildingSizeWidgetButtonClicked(FIntVector2 BroadcastedBuildingSize)
{
	UE_LOG(GridLog, Display, TEXT("Received new building size {%i, %i}"), BroadcastedBuildingSize.X, BroadcastedBuildingSize.Y);
	SetBuildingSize(BroadcastedBuildingSize);
}
