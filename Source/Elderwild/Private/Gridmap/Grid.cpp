#include "Gridmap/Grid.h"

#include "ProceduralMeshComponent.h"

#include "Gridmap/GridFactory.h"
#include "Gridmap/OccupancyMap.h"
#include "Gridmap/GridRenderData.h"
#include "Gridmap/GridVisuals.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	LinesProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Lines"));
	SelectionProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Selection"));
	GridDimensions = CreateDefaultSubobject<UGridDimensions>(TEXT("Grid Dimensions"));
	GridFactory = CreateDefaultSubobject<UGridFactory>(TEXT("Grid Factory"));
}

void AGrid::OnConstruction(const FTransform &Transform)
{
	checkf(GridVisuals, TEXT("No grid visuals given to the grid"));
	LineMaterial = CreateMaterialInstance(GridVisuals->LineColor, GridVisuals->LineOpacity);
	SetSelectionMaterialColour(GridVisuals->InspectColor);
	
	checkf(GridFactory, TEXT("Grid factory not created"));
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	GridFactory->SetGridDimensions(GridDimensions);
	FGridRenderData LinesRenderData = GridFactory->GenerateGridGeometry();
	FGridRenderData SelectionRenderData = GridFactory->GenerateSelectionSquareGeometry();
	
	CreateMeshSectionFromRenderData(LinesProceduralMesh, LinesRenderData);

	checkf(LineMaterial, TEXT("LineMaterial not generated properly"));
	LinesProceduralMesh->SetMaterial(0, LineMaterial);
	CreateMeshSectionFromRenderData(SelectionProceduralMesh, SelectionRenderData);
	SelectionProceduralMesh->SetVisibility(false);

	checkf(SelectionMaterial, TEXT("SelectionMaterial not generated properly"));
	SelectionProceduralMesh->SetMaterial(0, SelectionMaterial);
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	OccupancyMap = NewObject<UOccupancyMap>();
	checkf(OccupancyMap, TEXT("OccupancyMap not initialized properly"));
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	OccupancyMap->Init(GridDimensions->GetGridWidth(), GridDimensions->GetGridHeight());
}

void AGrid::CreateMeshSectionFromRenderData(UProceduralMeshComponent* Mesh, FGridRenderData& GridRenderData)
{
	checkf(Mesh, TEXT("Trying to create a mesh section with a nullptr procedural mesh component"));

	Mesh->CreateMeshSection(
		0,								// Which mesh section to write to
		GridRenderData.Vertices,
		GridRenderData.Triangles,
		TArray<FVector>(),				// Normals (empty)
		TArray<FVector2D>(),			// UV0 (empty)
		TArray<FColor>(),				// VertexColors (empty)
		TArray<FProcMeshTangent>(),		// Tangents (empty)
		false							// Collision not needed
	);
}

UMaterialInstanceDynamic* AGrid::CreateMaterialInstance(FLinearColor Color, float Opacity)
{
	checkf(GridVisuals, TEXT("No grid visuals given to the grid"));
	checkf(GridVisuals->Material, TEXT("AGrid cannot create dynamic material instance, because no parent material is set"));
	
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(GridVisuals->Material, this);
	DynMaterial->SetVectorParameterValue("Color", Color);
	DynMaterial->SetScalarParameterValue("Opacity", Opacity);
	
	return DynMaterial;
}

void AGrid::SetSelectedTile(FIntVector2 Coord)
{
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	FVector2D Location = GridDimensions->CornerOfTileToGridLocation(Coord);

	bool IsValidTile = GridDimensions->TileIsValid(Coord);
	
	checkf(SelectionProceduralMesh, TEXT("Selection procedural mesh is not initialized right"));
	SelectionProceduralMesh->SetVisibility(IsValidTile);

	if (IsValidTile)
	{
		FVector SelectionLocation = FVector(Location.X, Location.Y, GetActorLocation().Z);
		SelectionProceduralMesh->SetWorldLocation(SelectionLocation);
	}
}

void AGrid::HoverTile(FVector Location)
{
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	FIntVector2 Coord = GridDimensions->LocationToTile(Location);
	SetSelectedTile(Coord);
	SetSelectionMaterialBasedOnBuildValidity(Coord);
}

void AGrid::UnhoverTile()
{
	SetSelectedTile(FIntVector2(-1, -1));
}

void AGrid::TryBuild(FIntVector2 TileToBuildOn)
{
	if (!Building || !OccupancyMap) return;
	if (OccupancyMap->GetTileOccupancyState(TileToBuildOn) == EOccupancyState::OCCUPIED) return;

	UE_LOG(LogTemp, Display, TEXT("TryBuild"));

	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	FVector2D TileCenter = GridDimensions->CenterOfTileToGridLocation(TileToBuildOn);
	FVector LocalLocation = FVector(TileCenter.X, TileCenter.Y, GetActorLocation().Z);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AActor>(Building, LocalLocation, Rotation, SpawnInfo);
	
	OccupancyMap->SetTileOccupancyState(TileToBuildOn, EOccupancyState::OCCUPIED);
}

void AGrid::SetSelectionMaterialColour(FLinearColor NewColor)
{
	SelectionMaterial = CreateMaterialInstance(NewColor, GridVisuals->SelectionOpacity);

	if (SelectionProceduralMesh && SelectionMaterial)
	{
		SelectionProceduralMesh->SetMaterial(0, SelectionMaterial);
	}
}

void AGrid::SetSelectionMaterialBasedOnBuildValidity(FIntVector2 Coord)
{
	if (!GridDimensions || !OccupancyMap) return;
	if (!GridDimensions->TileIsValid(Coord)) return;
	if (!IsInBuildMode) return;

	if (OccupancyMap->GetTileOccupancyState(Coord) == EOccupancyState::EMPTY)
	{
		SetSelectionMaterialColour(GridVisuals->BuildValidColor);
	}
	else
	{
		SetSelectionMaterialColour(GridVisuals->BuildInvalidColor);
	}
}
