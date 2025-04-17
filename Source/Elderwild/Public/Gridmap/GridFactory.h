#pragma once

#include "Gridmap/GridDimensions.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridFactory.generated.h"

struct FGridRenderData;
struct FLine;

/** Handles logic relating to generating vertices and lines for the grid.
 *  Note that it does *NOT* create the mesh, but generates the geometry of it.
 *  The geometry is then passed to AGrid to generate.
 */
UCLASS()
class ELDERWILD_API UGridFactory : public UActorComponent
{
	GENERATED_BODY()

public:
	void SetGridDimensions(FGridDimensions NewGridDimensions);
	
	FGridRenderData GenerateGridGeometry();

	FGridRenderData GenerateSelectionSquareGeometry();

private:
	FGridDimensions GridDimensions;
	
	void CreateParallelHorizontalLines(FGridRenderData& GridRenderData);

	void CreateParallelVerticalLines(FGridRenderData& GridRenderData);

	void CreateLine(const FLine& Line, const float Thickness, FGridRenderData& GridRenderData);
};
