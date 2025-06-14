#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridFactory.generated.h"

struct FGridRenderData;
struct FLine;
class UProceduralMeshComponent;
class AGrid;

/** Handles logic relating to generating vertices and lines for the grid.
 *  Note that it does *NOT* create the mesh, but generates the geometry of it.
 *  The geometry is then passed to AGrid to generate.
 */
// TODO : move this to be a UObject
UCLASS()
class ELDERWILD_API UGridFactory : public UActorComponent
{
	GENERATED_BODY()

public:
	static FGridRenderData GenerateGridGeometry(AGrid* Grid);

	static void GenerateSelectionSquareGeometry(AGrid* Grid, UProceduralMeshComponent* Mesh);

	static void CreateMeshSectionFromRenderData(UProceduralMeshComponent* Mesh, FGridRenderData& GridRenderData);

private:
	static void CreateParallelHorizontalLines(FGridRenderData& GridRenderData, AGrid* Grid);

	static void CreateParallelVerticalLines(FGridRenderData& GridRenderData, AGrid* Grid);

	static void CreateLine(const FLine& Line, const float Thickness, FGridRenderData& GridRenderData);
};
