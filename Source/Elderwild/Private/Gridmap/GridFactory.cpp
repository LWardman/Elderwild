#include "Gridmap/GridFactory.h"

#include "ProceduralMeshComponent.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridRenderData.h"
#include "Gridmap/Line.h"
#include "Gridmap/GridDimensions.h"


FGridRenderData UGridFactory::GenerateGridGeometry(AGrid* Grid)
{
	FGridRenderData GridGeometry;
	CreateParallelHorizontalLines(GridGeometry, Grid);
	CreateParallelVerticalLines(GridGeometry, Grid);
	return GridGeometry;
}

// TODO : this should take in a max building size
void UGridFactory::GenerateSelectionSquareGeometry(AGrid* Grid, UProceduralMeshComponent* Mesh)
{
	checkf(Mesh, TEXT("Passed a nullptr for a mesh"));
	checkf(Grid, TEXT("Passed a nullptr for a grid"));
	const UGridDimensions* GridDimensions = Grid->GetGridDimensions();
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));

	float TileSize = GridDimensions->GetTileSize();
	float HalfTile = TileSize/2;
	FVector PivotOffset = {HalfTile, HalfTile, 0};

	int32 SectionCount = 0;
	
	for (int Height = 0; Height < 3; Height++)
	{
		for (int Width = 0; Width < 3; Width++)
		{
			FGridRenderData SelectionRenderData;
			
			float HeightOffset = TileSize * Height;
			float WidthOffset = TileSize * Width;
			
			FLine SelectionSquare;
			SelectionSquare.Start = FVector(WidthOffset, HeightOffset + HalfTile, 0);
			SelectionSquare.End = FVector(WidthOffset + TileSize, HeightOffset + HalfTile, 0);

			SelectionSquare.Start -= PivotOffset;
			SelectionSquare.End -= PivotOffset;

			CreateLine(SelectionSquare, TileSize, SelectionRenderData);

			Mesh->CreateMeshSection(
				SectionCount,					// Which mesh section to write to
				SelectionRenderData.Vertices,
				SelectionRenderData.Triangles,
				TArray<FVector>(),				// Normals (empty)
				TArray<FVector2D>(),			// UV0 (empty)
				TArray<FColor>(),				// VertexColors (empty)
				TArray<FProcMeshTangent>(),		// Tangents (empty)
				false							// Collision not needed
			);

			SectionCount++;
		}
	}
}

void UGridFactory::CreateMeshSectionFromRenderData(UProceduralMeshComponent* Mesh, FGridRenderData& GridRenderData)
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

void UGridFactory::CreateParallelHorizontalLines(FGridRenderData& GridRenderData, AGrid* Grid)
{
	checkf(Grid, TEXT("Passed a nullptr for a grid"));
	const UGridDimensions* GridDimensions = Grid->GetGridDimensions();
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	
	for (int32 i = 0; i <= GridDimensions->GetNumRows(); i++)
	{
		const float LineStart = i * GridDimensions->GetTileSize();
		const float LineEnd = GridDimensions->GetGridWidth();

		FLine Line;
		Line.Start = FVector(LineStart, 0, 0);
		Line.End = FVector(LineStart, LineEnd, 0);
		
		CreateLine(Line, GridDimensions->GetLineThickness(), GridRenderData);
	}
}

void UGridFactory::CreateParallelVerticalLines(FGridRenderData& GridRenderData, AGrid* Grid)
{
	checkf(Grid, TEXT("Passed a nullptr for a grid"));
	const UGridDimensions* GridDimensions = Grid->GetGridDimensions();
	checkf(GridDimensions, TEXT("GridDimensions not initialized properly"));
	
	for (int32 i = 0; i <= GridDimensions->GetNumCols(); i++)
	{
		const float LineStart = i * GridDimensions->GetTileSize();
		const float LineEnd = GridDimensions->GetGridHeight();

		FLine Line;
		Line.Start = FVector( 0, LineStart,0);
		Line.End = FVector( LineEnd, LineStart,0);
		
		CreateLine(Line, GridDimensions->GetLineThickness(), GridRenderData);
	}
}

void UGridFactory::CreateLine(const FLine& Line, const float Thickness, FGridRenderData& GridRenderData)
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
