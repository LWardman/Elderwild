#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridDimensions.generated.h"


UCLASS()
class ELDERWILD_API UGridDimensions : public UActorComponent
{
	GENERATED_BODY()

public:
	int32 GetGridWidth() const {return NumCols * TileSize;}
	int32 GetGridHeight() const {return NumRows * TileSize;}
	int32 GetTileSize() const {return TileSize;}
	int32 GetNumCols() const {return NumRows;}
	int32 GetNumRows() const {return NumCols;}
	int32 GetLineThickness() const {return LineThickness;}

	bool TileIsValid(const FIntVector2 Coord) const;
	bool TileHasValidDimensions() const;

	FVector2D CenterOfTileToGridLocation(FIntVector2 Coord);
    
	FVector2D CornerOfTileToGridLocation(FIntVector2 Coord);

	FIntVector2 LocationToTile(FVector HitLocation) const;
	
private:
	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 NumCols = 10;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 TileSize = 200;

	UPROPERTY(EditAnywhere, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 LineThickness = 10;

	FVector2D CenterAdjustment();

	FIntVector2 LocalLocationToTile(FVector LocalHitLocation) const;
};