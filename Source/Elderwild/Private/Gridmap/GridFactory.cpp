#include "Gridmap/GridFactory.h"

#include "Gridmap/GridRenderData.h"
#include "Gridmap/Line.h"

void UGridFactory::SetGridDimensions(FGridDimensions NewGridDimensions)
{
	GridDimensions = NewGridDimensions;
}

FGridRenderData UGridFactory::GenerateGridGeometry()
{
	FGridRenderData GridGeometry;
	CreateParallelHorizontalLines(GridGeometry);
	CreateParallelVerticalLines(GridGeometry);
	return GridGeometry;
}

FGridRenderData UGridFactory::GenerateSelectionSquareGeometry()
{
	FLine SelectionSquare;
	SelectionSquare.Start = FVector(0, GridDimensions.TileSize/2, 0);
	SelectionSquare.End = FVector(GridDimensions.TileSize, GridDimensions.TileSize/2, 0);
	FGridRenderData SelectionRenderData;
	CreateLine(SelectionSquare, GridDimensions.TileSize, SelectionRenderData);
	return SelectionRenderData;
}

void UGridFactory::CreateParallelHorizontalLines(FGridRenderData& GridRenderData)
{
	for (int32 i = 0; i <= GridDimensions.NumRows; i++)
	{
		const float LineStart = i * GridDimensions.TileSize;
		const float LineEnd = GridDimensions.GetGridWidth();

		FLine Line;
		Line.Start = FVector(LineStart, 0, 0);
		Line.End = FVector(LineStart, LineEnd, 0);
		
		CreateLine(Line, GridDimensions.LineThickness, GridRenderData);
	}
}

void UGridFactory::CreateParallelVerticalLines(FGridRenderData& GridRenderData)
{
	for (int32 i = 0; i <= GridDimensions.NumCols; i++)
	{
		const float LineStart = i * GridDimensions.TileSize;
		const float LineEnd = GridDimensions.GetGridHeight();

		FLine Line;
		Line.Start = FVector( 0, LineStart,0);
		Line.End = FVector( LineEnd, LineStart,0);
		
		CreateLine(Line, GridDimensions.LineThickness, GridRenderData);
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
