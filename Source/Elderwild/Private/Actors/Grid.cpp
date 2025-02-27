#include "Actors/Grid.h"

#include "ProceduralMeshComponent.h"

// Sets default values
AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh Component"));
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
	
	if (ProceduralMesh)
	{
		ProceduralMesh->CreateMeshSection(
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
			ProceduralMesh->SetMaterial(0, LineMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("LineMaterial not generated properly"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Grid cannot be created, as no procedural mesh is assigned"));
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
		UE_LOG(LogTemp, Error,
			TEXT("AGrid cannot create dynamic material instance, because no parent material is set. "
							"Returning nullptr."));
		return nullptr;
	}
	
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	DynMaterial->SetVectorParameterValue("Color", LineColor);
	DynMaterial->SetScalarParameterValue("Opacity", LineOpacity);
	
	return DynMaterial;
}

void AGrid::LocationToTile(FVector Location, int32& GridRow, int32& GridCol, bool& IsValid)
{
	
}

void AGrid::TileToGridLocation(int32 Row, int32 Col, bool ShouldCenter, bool& IsValid, FVector2D& Location)
{
	
}

void AGrid::SetSelectedTile(int32 Row, int32 Col)
{
	
}

bool AGrid::TileIsValid(int32 Row, int32 Col)
{
	return true;
}