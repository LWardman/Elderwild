#include "Actors/Grid.h"

#include "ProceduralMeshComponent.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	LinesProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Lines"));
	SelectionProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component for Selection"));
}

void AGrid::OnConstruction(const FTransform &Transform)
{
	LineMaterial = CreateMaterialInstance(LineColor, LineOpacity);
	SelectionMaterial = CreateMaterialInstance(SelectionColor, SelectionOpacity);
	
	TArray<FVector> Vertices;
	TArray<int32> Triangles;

	CreateParallelHorizontalLines(Vertices, Triangles);

	CreateParallelVerticalLines(Vertices, Triangles);
	
	checkf(LinesProceduralMesh, TEXT("LinesProceduralMesh is not assigned"));
	CreateMeshSectionFromVerticesAndTriangles(LinesProceduralMesh, Vertices, Triangles);

	checkf(LineMaterial, TEXT("LineMaterial not generated properly"));
	LinesProceduralMesh->SetMaterial(0, LineMaterial);

	checkf(SelectionProceduralMesh, TEXT("SelectionProceduralMesh is not assigned"));
	
	FVector SelectionStart = FVector(0, TileSize/2, 0);
	FVector SelectionEnd = FVector(TileSize, TileSize/2, 0);
	TArray<FVector> SelectionVertices;
	TArray<int32> SelectionTriangles;
	CreateLine(SelectionStart, SelectionEnd, TileSize, SelectionVertices, SelectionTriangles);

	CreateMeshSectionFromVerticesAndTriangles(SelectionProceduralMesh, Vertices, Triangles);

	SelectionProceduralMesh->SetVisibility(false);

	checkf(SelectionMaterial, TEXT("SelectionMaterial not generated properly"));
	SelectionProceduralMesh->SetMaterial(0, SelectionMaterial);
}

void AGrid::CreateParallelHorizontalLines(TArray<FVector>& Vertices, TArray<int32>& Triangles)
{
	for (int32 i = 0; i <= NumRows; i++)
	{
		const float LineStart = i * TileSize;
		const float LineEnd = GetGridWidth();
		
		const FVector Start = FVector(LineStart, 0, 0);
		const FVector End = FVector(LineStart, LineEnd, 0);
		
		CreateLine(Start, End, LineThickness, Vertices, Triangles);
	}
}

void AGrid::CreateParallelVerticalLines(TArray<FVector>& Vertices, TArray<int32>& Triangles)
{
	for (int32 i = 0; i <= NumCols; i++)
	{
		const float LineStart = i * TileSize;
		const float LineEnd = GetGridHeight();
		
		const FVector Start = FVector( 0, LineStart,0);
		const FVector End = FVector( LineEnd, LineStart,0);
		
		CreateLine(Start, End, LineThickness, Vertices, Triangles);
	}
}

void AGrid::CreateMeshSectionFromVerticesAndTriangles(UProceduralMeshComponent* Mesh, TArray<FVector>& Vertices, TArray<int32>& Triangles)
{
	checkf(Mesh, TEXT("Trying to create a mesh section with a nullptr procedural mesh component"));

	Mesh->CreateMeshSection(
		0,								// Which mesh section to write to
		Vertices,
		Triangles,
		TArray<FVector>(),				// Normals (empty)
		TArray<FVector2D>(),			// UV0 (empty)
		TArray<FColor>(),				// VertexColors (empty)
		TArray<FProcMeshTangent>(),		// Tangents (empty)
		false							// Collision not needed
	);
}

void AGrid::CreateLine(const FVector Start, const FVector End, const float Thickness, TArray<FVector>& Vertices, TArray<int32>& Triangles)
{
	const float HalfThickness = Thickness / 2;

	FVector LineVector = End - Start;
	FVector LineVectorNormalized = LineVector.GetSafeNormal();
	FVector ThicknessDirection = FVector::CrossProduct(LineVectorNormalized, FVector::UnitZ());

	int32 VerticesLength = Vertices.Num();
	
	TArray<int32> TriangleIndices = {VerticesLength + 2, VerticesLength + 1, VerticesLength + 0,
									 VerticesLength + 2, VerticesLength + 3, VerticesLength + 1};

	Triangles.Append(TriangleIndices);

	FVector VertexZero = Start + HalfThickness * ThicknessDirection;
	FVector VertexOne = VertexZero + LineVector;
	FVector VertexTwo = VertexZero - Thickness * ThicknessDirection;
	FVector VertexThree = VertexTwo + LineVector;

	TArray<FVector> CalculatedVertices = {VertexZero, VertexOne, VertexTwo, VertexThree};
	Vertices.Append(CalculatedVertices);
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
	checkf(Grid, TEXT("AGrid cannot create dynamic material instance, because no parent material is set"));
	
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	DynMaterial->SetVectorParameterValue("Color", Color);
	DynMaterial->SetScalarParameterValue("Opacity", Opacity);
	
	return DynMaterial;
}

void AGrid::LocationToTile(FVector Location, int32& GridRow, int32& GridCol)
{
	checkf((GetGridWidth() != 0), TEXT("Grid has width zero, don't divide by 0"));
	checkf((GetGridHeight() != 0), TEXT("Grid has height zero, don't divide by 0"));

	FVector GridLocation = GetActorLocation();
	FVector LocalHitLocation = Location - GridLocation;

	GridRow = FMath::Floor((LocalHitLocation.X / GetGridWidth()) * NumRows);
	GridCol = FMath::Floor((LocalHitLocation.Y / GetGridHeight()) * NumCols);
}

void AGrid::TileToGridLocation(int32 Row, int32 Col, bool ShouldCenter, FVector2D& Location)
{
	if (!TileIsValid(Row, Col)) return;
	
	float CenterAdjustment = ShouldCenter * TileSize / 2;
	float TileCornerX = Row * TileSize + GetActorLocation().X;
	float TileCornerY = Col * TileSize + GetActorLocation().Y;

	Location.X = TileCornerX + CenterAdjustment;
	Location.Y = TileCornerY + CenterAdjustment;
}

void AGrid::SetSelectedTile(int32 Row, int32 Col)
{
	FVector2D Location;
	TileToGridLocation(Row, Col, false, Location);
	
	checkf(SelectionProceduralMesh, TEXT("Selection procedural mesh is not initialized right"));
	SelectionProceduralMesh->SetVisibility(TileIsValid(Row, Col));

	if (TileIsValid(Row, Col))
	{
		FVector SelectionLocation = FVector(Location.X, Location.Y, GetActorLocation().Z);
		SelectionProceduralMesh->SetWorldLocation(SelectionLocation);
	}
}

bool AGrid::TileIsValid(int32 Row, int32 Col)
{
	bool RowIsValid = (Row >= 0 && Row < NumRows);
	bool ColIsValid = (Col >= 0 && Col < NumCols);
	return RowIsValid && ColIsValid;
}