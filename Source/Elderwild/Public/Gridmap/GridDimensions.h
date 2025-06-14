#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridDimensions.generated.h"

class AGrid;

UCLASS()
class ELDERWILD_API UGridDimensions : public UActorComponent
{
	GENERATED_BODY()

public:
	UGridDimensions();

	void Init(int32 _NumRows, int32 _NumCols, int32 _TileSize, int32 _LineThickness);
	
	int32 GetNumCols() const {return NumCols;}
	int32 GetNumRows() const {return NumRows;}
	int32 GetTileSize() const {return TileSize;}
	
	int32 GetGridWidth() const {return NumCols * TileSize;}
	int32 GetGridHeight() const {return NumRows * TileSize;}
	
	int32 GetLineThickness() const {return LineThickness;}

	FVector2D CenterOfTileToGridLocation(FIntVector2 Coord);
    
	FVector2D CornerOfTileToGridLocation(FIntVector2 Coord);

	bool TileIsValid(const FIntVector2 Coord) const;

	static FIntVector2 LocationToTile(FVector HitLocation, AGrid* Grid);
	
private:
	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumCols = 10;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 TileSize = 200;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 LineThickness = 10;

	bool GridHasValidDimensions() const;

	FVector2D CenterAdjustment();

	FIntVector2 LocalLocationToTile(FVector LocalHitLocation) const;

	FVector GetWorldLocation() const;
};