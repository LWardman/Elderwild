#include "Gridmap/Grid.h"

#include "ProceduralMeshComponent.h"
#include "Buildings/Building.h"

#include "Gridmap/GridFactory.h"
#include "Gridmap/OccupancyMap.h"
#include "Gridmap/GridRenderData.h"
#include "Gridmap/GridVisuals.h"
#include "Gridmap/SelectionTile.h"
#include "Gridmap/GridDimensions.h"
#include "Buildings/BuildingDirection.h"
#include "Buildings/BuildingData.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	LinesProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Lines"));
	SelectionTile = CreateDefaultSubobject<USelectionTile>(TEXT("Procedural Mesh Component for Selection"));
	GridDimensions = CreateDefaultSubobject<UGridDimensions>(TEXT("Grid Dimensions"));
	GridFactory = CreateDefaultSubobject<UGridFactory>(TEXT("Grid Factory"));
}

void AGrid::OnConstruction(const FTransform &Transform)
{
	checkf(GridVisuals, TEXT("No grid visuals given to the grid"));
	LineMaterial = UGridVisuals::CreateMaterialInstance(GridVisuals->LineColor, GridVisuals->LineOpacity, this);
	SetSelectionMaterialColour(GridVisuals->InspectColor);
	
	checkf(GridFactory, TEXT("Grid factory not created"));
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	FGridRenderData LinesRenderData = UGridFactory::GenerateGridGeometry(this);
	UGridFactory::CreateMeshSectionFromRenderData(LinesProceduralMesh, LinesRenderData);

	checkf(LineMaterial, TEXT("LineMaterial not generated properly"));
	LinesProceduralMesh->SetMaterial(0, LineMaterial);
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	OccupancyMap = NewObject<UOccupancyMap>();
	checkf(OccupancyMap, TEXT("OccupancyMap not initialized properly"));
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	OccupancyMap->Init(GridDimensions->GetNumCols(), GridDimensions->GetNumRows());

	checkf(SelectionTile, TEXT("Selection tile not properly generated"));
	SelectionTile->Init(this);
}

void AGrid::HoverTile(FVector Location)
{
	FIntVector2 Coord = UGridDimensions::LocationToTile(Location, this);
	SetSelectedTile(Coord);
}

void AGrid::UnhoverTile()
{
	SetSelectedTile(FIntVector2(-1, -1));
}

// TODO : refactor. time for a building component? Should this class even be building stuff?
void AGrid::TryBuild(FIntVector2 TileToBuildOn)
{
	if (!BuildingData || !BuildingData->BuildingClass || !OccupancyMap || !SelectionTile || !GridDimensions) return;
	
	FIntVector2 BuildingSize = BuildingData->BuildingSize;
	TArray<FIntVector2> RelevantTiles = SelectionTile->CalculateRelevantTileLocations(TileToBuildOn, BuildingSize);

	if (!OccupancyMap->AllTilesHaveState(RelevantTiles, EOccupancyState::EMPTY)) return;
	
	float BuildingOffsetX = float(BuildingSize.X - 1) / 2;
	float BuildingOffsetY = float(BuildingSize.Y - 1) / 2;
	FVector2D Offset = {BuildingOffsetX, BuildingOffsetY};
	
	ECompassDirection CompassDirection = UBuildingDirection::GetDirection();
	Offset = UBuildingDirection::CentreOffsetMultiplier(Offset, CompassDirection);
	Offset *= GridDimensions->GetTileSize();

	FVector2D BuildingCentre = GridDimensions->CenterOfTileToGridLocation(TileToBuildOn) + Offset;
	FVector LocalLocation = FVector(BuildingCentre.X, BuildingCentre.Y, GetActorLocation().Z);
	FRotator Rotation = UBuildingDirection::DirectionToRotator(CompassDirection);

	FActorSpawnParameters SpawnInfo;
	ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(BuildingData->BuildingClass, LocalLocation, Rotation, SpawnInfo);
	Building->BuildingDirection = CompassDirection;

	OccupancyMap->SetGroupTileOccupancyState(RelevantTiles, EOccupancyState::OCCUPIED);
}

void AGrid::SetSelectionMaterialColour(FLinearColor NewColor)
{
	if (SelectionTile)
	{
		SelectionTile->SetSelectionMaterialColour(NewColor);
	}
}

void AGrid::SetSelectedTile(FIntVector2 Coord)
{
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	FVector2D Location = GridDimensions->CenterOfTileToGridLocation(Coord);
	FVector SelectionLocation = FVector(Location.X, Location.Y, GetActorLocation().Z);

	bool IsValidTile = GridDimensions->TileIsValid(Coord);

	if (SelectionTile)
	{
		SelectionTile->UpdateSelectedTile(IsValidTile, SelectionLocation);
	}
}

void AGrid::SetSelectionMaterialBasedOnBuildValidity(FIntVector2 Coord)
{
	if (GridDimensions && !GridDimensions->TileIsValid(Coord)) return;

	if (OccupancyMap && OccupancyMap->GetTileOccupancyState(Coord) == EOccupancyState::EMPTY)
	{
		SetSelectionMaterialColour(GridVisuals->BuildValidColor);
		return;
	}
	SetSelectionMaterialColour(GridVisuals->BuildInvalidColor);
}
