#pragma once

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
	FGridRenderData GenerateGridGeometry();

	FGridRenderData GenerateSelectionSquareGeometry();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumCols = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 TileSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 LineThickness = 10;
	
	void CreateParallelHorizontalLines(FGridRenderData& GridRenderData);

	void CreateParallelVerticalLines(FGridRenderData& GridRenderData);

	// TODO : DRY
	int32 GetGridWidth() const {return NumCols * TileSize;}

	int32 GetGridHeight() const {return NumRows * TileSize;}

	void CreateLine(const FLine& Line, const float Thickness, FGridRenderData& GridRenderData);

	
};
