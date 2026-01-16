#include "Gridmap/Grid.h"

#include "ProceduralMeshComponent.h"
#include "Buildings/Building.h"
#include "Kismet/GameplayStatics.h"

#include "Gridmap/GridFactory.h"
#include "Gridmap/OccupancyMap.h"
#include "Gridmap/GridRenderData.h"
#include "Gridmap/GridVisuals.h"
#include "Gridmap/SelectionTile.h"
#include "Gridmap/GridDimensions.h"
#include "Buildings/BuildingDirection.h"
#include "Buildings/BuildingData.h"
#include "Logging/GridLog.h"
#include "Buildings/BuildingMenu/BuildingMenu.h"

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
	
	CreateBuildingMenuWidget();
}

void AGrid::HoverTile(FVector Location)
{
	FIntVector2 Coord = UGridDimensions::LocationToTile(Location, this);
	SetSelectedTile(Coord);
	
	if (DisplayBuilding && GetGridDimensions())
	{
		const bool bShouldBeHidden = !GetGridDimensions()->TileIsValid(Coord);
		FString Hidden = bShouldBeHidden ? "False" : "True";
		DisplayBuilding->SetActorHiddenInGame(bShouldBeHidden);
		HandleDisplayBuildingMovement(Coord);
	}
}

void AGrid::UnhoverTile()
{
	SetSelectedTile(FIntVector2(-1, -1));
	
	if (DisplayBuilding) DisplayBuilding->SetActorHiddenInGame(true);
}

// TODO : refactor. time for a building component? Should this class even be building stuff?
void AGrid::TryBuild(FIntVector2 TileToBuildOn)
{
	if (!BuildingData || !BuildingData->BuildingClass || !OccupancyMap || !SelectionTile || !GridDimensions) return;
	
	FIntVector2 BuildingSize = BuildingData->BuildingSize;
	TArray<FIntVector2> RelevantTiles = SelectionTile->CalculateRelevantTileLocations(TileToBuildOn);

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

void AGrid::SetBuildingData(const UBuildingData* InBuildingData)
{
	if (!InBuildingData) return;
	
	BuildingData = InBuildingData;
	BuildingDataUpdated.Broadcast(InBuildingData);
}

void AGrid::CreateDisplayBuilding()
{
	if (!BuildingData || !BuildingData->OpaqueBuildingClass)
	{
		UE_LOG(GridLog, Warning, TEXT("Received a null building data or a null opaque class"));
		return;
	}
	
	FActorSpawnParameters SpawnInfo;
	ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(BuildingData->OpaqueBuildingClass,
													FVector::Zero(),
													FRotator::ZeroRotator,
													SpawnInfo);
	if (Building)
	{
		UE_LOG(GridLog, Display, TEXT("Successfully created display building : %s"), *Building->GetName());
		Building->SetActorHiddenInGame(true);
		DisplayBuilding = Building;
	}
}

void AGrid::DestroyDisplayBuilding()
{
	if (!DisplayBuilding) return;
	
	UE_LOG(GridLog, Display, TEXT("Destroying DisplayBuilding"));
	DisplayBuilding->Destroy();	
	DisplayBuilding = nullptr;
}

void AGrid::HandleDisplayBuildingMovement(FIntVector2 NewLocation)
{
	if (!DisplayBuilding || !BuildingData) return;
	
	ECompassDirection CompassDirection = UBuildingDirection::GetDirection();
	FRotator Rotation = UBuildingDirection::DirectionToRotator(CompassDirection);
	DisplayBuilding->SetActorRotation(Rotation);
	
	FIntVector2 BuildingSize = BuildingData->BuildingSize;
	float BuildingOffsetX = float(BuildingSize.X - 1) / 2;
	float BuildingOffsetY = float(BuildingSize.Y - 1) / 2;
	FVector2D Offset = {BuildingOffsetX, BuildingOffsetY};
	Offset = UBuildingDirection::CentreOffsetMultiplier(Offset, CompassDirection);
	Offset *= GridDimensions->GetTileSize();
	
	FVector2D BuildingCentre = GridDimensions->CenterOfTileToGridLocation(NewLocation) + Offset;
	FVector LocalLocation = FVector(BuildingCentre.X, BuildingCentre.Y, GetActorLocation().Z);
	DisplayBuilding->SetActorLocation(LocalLocation);
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
void AGrid::CreateBuildingMenuWidget()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (Controller && BuildingMenuClass)
	{
		BuildingMenuWidget = CreateWidget<UBuildingMenu>(Controller, BuildingMenuClass);
		
		if (BuildingMenuWidget)
		{
			BuildingMenuWidget->BuildingSelected.AddDynamic(this, &AGrid::OnBuildingButtonClicked);
			BuildingMenuWidget->AddToPlayerScreen();
			UE_LOG(GridLog, Display, TEXT("Adding Building Menu to the players screen"));
		}
	}
}

void AGrid::OnBuildingButtonClicked(const UBuildingData* InBuildingData)
{
	UE_LOG(GridLog, Display, TEXT("Setting BuildingData"));
	SetBuildingData(InBuildingData);
}
