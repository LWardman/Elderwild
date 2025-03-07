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

	for (int32 i = 0; i <= NumRows; i++)
	{
		const float LineStart = i * TileSize;
		const float LineEnd = GetGridWidth();
		
		const FVector Start = FVector(LineStart, 0, 0);
		const FVector End = FVector(LineStart, LineEnd, 0);
		
		CreateLine(Start, End, LineThickness, Vertices, Triangles);
	}

	for (int32 i = 0; i <= NumCols; i++)
	{
		const float LineStart = i * TileSize;
		const float LineEnd = GetGridHeight();
		
		const FVector Start = FVector( 0, LineStart,0);
		const FVector End = FVector( LineEnd, LineStart,0);
		
		CreateLine(Start, End, LineThickness, Vertices, Triangles);
	}
	
	if (LinesProceduralMesh)
	{
		LinesProceduralMesh->CreateMeshSection(
			0,
			Vertices,
			Triangles,
			TArray<FVector>(),				// Normals (empty)
			TArray<FVector2D>(),			// UV0 (empty)
			TArray<FColor>(),				// VertexColors (empty)
			TArray<FProcMeshTangent>(),		// Tangents (empty)
			false							// Collision not needed
		);

		if (LineMaterial)
		{
			LinesProceduralMesh->SetMaterial(0, LineMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("LineMaterial not generated properly"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grid cannot be created, as no procedural mesh is assigned"));
	}

	if (SelectionProceduralMesh)
	{
		FVector SelectionStart = FVector(0, TileSize/2, 0);
		FVector SelectionEnd = FVector(TileSize, TileSize/2, 0);
		TArray<FVector> SelectionVertices;
		TArray<int32> SelectionTriangles;
		CreateLine(SelectionStart, SelectionEnd, TileSize, SelectionVertices, SelectionTriangles);

		SelectionProceduralMesh->CreateMeshSection(
			0,
			SelectionVertices,
			SelectionTriangles,
			TArray<FVector>(),				// Normals (empty)
			TArray<FVector2D>(),			// UV0 (empty)
			TArray<FColor>(),				// VertexColors (empty)
			TArray<FProcMeshTangent>(),		// Tangents (empty)
			false							// Collision not needed
		);

		SelectionProceduralMesh->SetVisibility(false);

		if (SelectionMaterial)
		{
			SelectionProceduralMesh->SetMaterial(0, SelectionMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SelectionMaterial not generated properly"));
		}
	}
	
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	// Keep an eye on this as it might append an array
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
	if (!Material)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("AGrid cannot create dynamic material instance, because no parent material is set. "
							"Returning nullptr."));
		return nullptr;
	}
	
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	DynMaterial->SetVectorParameterValue("Color", Color);
	DynMaterial->SetScalarParameterValue("Opacity", Opacity);
	
	return DynMaterial;
}

void AGrid::LocationToTile(FVector Location, int32& GridRow, int32& GridCol, bool& IsValid)
{
	FVector GridLocation = GetActorLocation();
	FVector LocalHitLocation = Location - GridLocation;

	if (GetGridWidth() == 0 || GetGridHeight() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Dividing by 0 when calculating cursor location to tile, check grid dimensions"));
		return;
	}

	GridRow = FMath::Floor((LocalHitLocation.X / GetGridWidth()) * NumRows);
	GridCol = FMath::Floor((LocalHitLocation.Y / GetGridHeight()) * NumCols);

	IsValid = TileIsValid(GridRow, GridCol);
	UE_LOG(LogTemp, Warning, TEXT("IsValid value is %s"), ( IsValid ? TEXT("true"): TEXT("false") ));
}

void AGrid::TileToGridLocation(int32 Row, int32 Col, bool ShouldCenter, bool& IsValid, FVector2D& Location)
{
	if (TileIsValid(Row, Col))
	{
		float CenterAdjustment = ShouldCenter * TileSize / 2;
		float TileCornerX = Row * TileSize + GetActorLocation().X;
		float TileCornerY = Col * TileSize + GetActorLocation().Y;

		Location.X = TileCornerX + CenterAdjustment;
		Location.Y = TileCornerY + CenterAdjustment;

		IsValid = true;
	}
}

void AGrid::SetSelectedTile(int32 Row, int32 Col)
{
	bool IsValid = false;
	FVector2D Location;
	TileToGridLocation(Row, Col, false, IsValid, Location);

	bool SelectionMeshIsValid = (SelectionProceduralMesh != nullptr);
	
	if (!SelectionProceduralMesh) return;
	
	SelectionProceduralMesh->SetVisibility(IsValid);


	if (IsValid)
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