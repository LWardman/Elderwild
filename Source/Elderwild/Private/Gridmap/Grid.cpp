#include "Gridmap/Grid.h"

#include "ProceduralMeshComponent.h"
#include "Gridmap/OccupancyMap.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	LinesProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Lines"));
	SelectionProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Selection"));
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	OccupancyMap = NewObject<UOccupancyMap>();
	checkf(OccupancyMap, TEXT("OccupancyMap not initialized properly"));
	OccupancyMap->Init(GetGridWidth(), GetGridHeight());
}

void AGrid::OnConstruction(const FTransform &Transform)
{
	LineMaterial = CreateMaterialInstance(LineColor, LineOpacity);
	SelectionMaterial = CreateMaterialInstance(SelectionColor, SelectionOpacity);
	
	FGridRenderData LinesRenderData;
	CreateParallelHorizontalLines(LinesRenderData);
	CreateParallelVerticalLines(LinesRenderData);
	
	checkf(LinesProceduralMesh, TEXT("LinesProceduralMesh is not assigned"));
	CreateMeshSectionFromVerticesAndTriangles(LinesProceduralMesh, LinesRenderData);

	checkf(LineMaterial, TEXT("LineMaterial not generated properly"));
	LinesProceduralMesh->SetMaterial(0, LineMaterial);

	FLine SelectionLine;
	SelectionLine.Start = FVector(0, TileSize/2, 0);
	SelectionLine.End = FVector(TileSize, TileSize/2, 0);
	FGridRenderData SelectionRenderData;
	CreateLine(SelectionLine, TileSize, SelectionRenderData);

	checkf(SelectionProceduralMesh, TEXT("SelectionProceduralMesh is not assigned"));
	CreateMeshSectionFromVerticesAndTriangles(SelectionProceduralMesh, SelectionRenderData);

	SelectionProceduralMesh->SetVisibility(false);

	checkf(SelectionMaterial, TEXT("SelectionMaterial not generated properly"));
	SelectionProceduralMesh->SetMaterial(0, SelectionMaterial);
}

void AGrid::CreateParallelHorizontalLines(FGridRenderData& GridRenderData)
{
	for (int32 i = 0; i <= NumRows; i++)
	{
		const float LineStart = i * TileSize;
		const float LineEnd = GetGridWidth();

		FLine Line;
		Line.Start = FVector(LineStart, 0, 0);
		Line.End = FVector(LineStart, LineEnd, 0);
		
		CreateLine(Line, LineThickness, GridRenderData);
	}
}

void AGrid::CreateParallelVerticalLines(FGridRenderData& GridRenderData)
{
	for (int32 i = 0; i <= NumCols; i++)
	{
		const float LineStart = i * TileSize;
		const float LineEnd = GetGridHeight();

		FLine Line;
		Line.Start = FVector( 0, LineStart,0);
		Line.End = FVector( LineEnd, LineStart,0);
		
		CreateLine(Line, LineThickness, GridRenderData);
	}
}

void AGrid::CreateMeshSectionFromVerticesAndTriangles(UProceduralMeshComponent* Mesh, FGridRenderData& GridRenderData)
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

void AGrid::CreateLine(const FLine& Line, const float Thickness, FGridRenderData& GridRenderData)
{
	const float HalfThickness = Thickness / 2;

	FVector LineVector = Line.End - Line.Start;
	FVector LineVectorNormalized = LineVector.GetSafeNormal();
	FVector ThicknessDirection = FVector::CrossProduct(LineVectorNormalized, FVector::UnitZ());

	int32 VerticesLength = GridRenderData.Vertices.Num();
	
	TArray<int32> TriangleIndices = {VerticesLength + 2, VerticesLength + 1, VerticesLength + 0,
									 VerticesLength + 2, VerticesLength + 3, VerticesLength + 1};

	GridRenderData.Triangles.Append(TriangleIndices);

	FVector VertexZero = Line.Start + HalfThickness * ThicknessDirection;
	FVector VertexOne = VertexZero + LineVector;
	FVector VertexTwo = VertexZero - Thickness * ThicknessDirection;
	FVector VertexThree = VertexTwo + LineVector;

	TArray<FVector> CalculatedVertices = {VertexZero, VertexOne, VertexTwo, VertexThree};
	GridRenderData.Vertices.Append(CalculatedVertices);
}

int32 AGrid::GetGridWidth() const
{
	return NumCols * TileSize;
}

int32 AGrid::GetGridHeight() const 
{
	return NumRows * TileSize;
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
	checkf(GetGridWidth() != 0, TEXT("Grid has width zero, don't divide by 0"));
	checkf(GetGridHeight() != 0, TEXT("Grid has height zero, don't divide by 0"));

	const FVector GridLocation = GetActorLocation();
	const FVector LocalHitLocation = Location - GridLocation;

	FIntVector2 TileLocation;
	TileLocation.X = FMath::Floor((LocalHitLocation.X / GetGridWidth()) * NumRows);
	TileLocation.Y = FMath::Floor((LocalHitLocation.Y / GetGridHeight()) * NumCols);

	return TileLocation;
}

FVector2D AGrid::CornerOfTileToGridLocation(FIntVector2 Coord)
{
	float TileCornerX = Coord.X * TileSize + GetActorLocation().X;
	float TileCornerY = Coord.Y * TileSize + GetActorLocation().Y;
	return FVector2D{TileCornerX, TileCornerY};
}

FVector2D AGrid::CenterOfTileToGridLocation(FIntVector2 Coord)
{
	float HalfTileLength = TileSize / 2;
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
	bool RowIsValid = (Coord.X >= 0 && Coord.X < NumRows);
	bool ColIsValid = (Coord.Y >= 0 && Coord.Y < NumCols);
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
