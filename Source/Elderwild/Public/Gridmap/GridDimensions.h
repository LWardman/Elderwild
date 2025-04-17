#pragma once

#include "CoreMinimal.h"
#include "GridDimensions.generated.h"
// TODO : move related functions here.
USTRUCT()
struct FGridDimensions
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumCols = 10;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 TileSize = 10;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 LineThickness = 10;

	int32 GetGridWidth() const {return NumCols * TileSize;}

	int32 GetGridHeight() const {return NumRows * TileSize;}
};