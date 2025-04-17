#include "Gridmap/Grid.h"

#include "ProceduralMeshComponent.h"

#include "Gridmap/GridFactory.h"
#include "Gridmap/OccupancyMap.h"
#include "Gridmap/GridRenderData.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	LinesProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Lines"));
	SelectionProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Selection"));
	GridFactory = CreateDefaultSubobject<UGridFactory>(TEXT("Grid Factory"));
}

void AGrid::OnConstruction(const FTransform &Transform)
{
	LineMaterial = CreateMaterialInstance(LineColor, LineOpacity);
	SelectionMaterial = CreateMaterialInstance(SelectionColor, SelectionOpacity);
	
	checkf(GridFactory, TEXT("Grid factory not created"));
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
	OccupancyMap->Init(GridDimensions.GetGridWidth(), GridDimensions.GetGridHeight());
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
	checkf(Material, TEXT("AGrid cannot create dynamic material instance, because no parent material is set"));
	
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	DynMaterial->SetVectorParameterValue("Color", Color);
	DynMaterial->SetScalarParameterValue("Opacity", Opacity);
	
	return DynMaterial;
}

FIntVector2 AGrid::LocationToTile(FVector Location)
{
	checkf(GridDimensions.GetGridWidth() != 0, TEXT("Grid has width zero, don't divide by 0"));
	checkf(GridDimensions.GetGridHeight() != 0, TEXT("Grid has height zero, don't divide by 0"));

	const FVector GridLocation = GetActorLocation();
	const FVector LocalHitLocation = Location - GridLocation;

	FIntVector2 TileLocation;
	TileLocation.X = FMath::Floor((LocalHitLocation.X / GridDimensions.GetGridWidth()) * GridDimensions.NumRows);
	TileLocation.Y = FMath::Floor((LocalHitLocation.Y / GridDimensions.GetGridHeight()) * GridDimensions.NumCols);

	return TileLocation;
}

FVector2D AGrid::CornerOfTileToGridLocation(FIntVector2 Coord)
{
	float TileCornerX = Coord.X * GridDimensions.TileSize + GetActorLocation().X;
	float TileCornerY = Coord.Y * GridDimensions.TileSize + GetActorLocation().Y;
	return FVector2D{TileCornerX, TileCornerY};
}

FVector2D AGrid::CenterOfTileToGridLocation(FIntVector2 Coord)
{
	float HalfTileLength = GridDimensions.TileSize / 2;
	FVector2D CenterAdjustment = FVector2D{HalfTileLength, HalfTileLength};
	return CornerOfTileToGridLocation(Coord) + CenterAdjustment;
}

void AGrid::SetSelectedTile(FIntVector2 Coord)
{
	FVector2D Location = CornerOfTileToGridLocation(Coord);
	
	checkf(SelectionProceduralMesh, TEXT("Selection procedural mesh is not initialized right"));
	SelectionProceduralMesh->SetVisibility(TileIsValid(Coord));

	if (TileIsValid(Coord))
	{
		FVector SelectionLocation = FVector(Location.X, Location.Y, GetActorLocation().Z);
		SelectionProceduralMesh->SetWorldLocation(SelectionLocation);
	}
}

bool AGrid::TileIsValid(FIntVector2 Coord)
{
	bool RowIsValid = (Coord.X >= 0 && Coord.X < GridDimensions.NumRows);
	bool ColIsValid = (Coord.Y >= 0 && Coord.Y < GridDimensions.NumCols);
	return RowIsValid && ColIsValid;
}

void AGrid::HoverTile(FVector Location)
{
	FIntVector2 Coord = LocationToTile(Location);
	SetSelectedTile(Coord);
}

void AGrid::UnhoverTile()
{
	SetSelectedTile(FIntVector2(-1, -1));
}

void AGrid::TryBuild(FIntVector2 TileToBuildOn)
{
	if (!Building || !OccupancyMap) return;
	if (OccupancyMap->GetTileOccupancyState(TileToBuildOn) == OCCUPIED) return;

	UE_LOG(LogTemp, Display, TEXT("TryBuild"));
	
	FVector2D TileCenter = CenterOfTileToGridLocation(TileToBuildOn);
	FVector LocalLocation = FVector(TileCenter.X, TileCenter.Y, GetActorLocation().Z);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AActor>(Building, LocalLocation, Rotation, SpawnInfo);
	
	OccupancyMap->SetTileOccupancyState(TileToBuildOn, OCCUPIED);
}
