#include "Actors/Grid.h"

#include "ProceduralMeshComponent.h"

// Sets default values
AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	LineMaterial = CreateMaterialInstance(LineColor, LineOpacity);
	SelectionMaterial = CreateMaterialInstance(SelectionColor, SelectionOpacity);

	for (int32 i = 0; i < NumRows; i++)
	{
		float LineStart = i * TileSize;
		float LineEnd = GetGridWidth();

		TArray<FVector> Vertices;
		TArray<int32> Triangles;

		// LEFT OFF HERE
		//FVector Start = FVector(LineStart);
		//FVector End = FVector(LineStart, LineEnd);
		
		//CreateLine(Start, End, LineOpacity, Vertices, Triangles);
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

void AGrid::CreateLine(FVector Start, FVector End, float Thickness, TArray<FVector> Vertices, TArray<int32> Triangles)
{
	
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