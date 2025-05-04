#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OccupancyMap.generated.h"

UENUM(BlueprintType)
enum class EOccupancyState : uint8
{
	EMPTY,
	OCCUPIED,
	NOT_A_TILE
};

typedef TArray<TArray<EOccupancyState>> OccupancyMatrix;

UCLASS()
class ELDERWILD_API UOccupancyMap : public UObject
{
	GENERATED_BODY()

public:
	void Init(int32 _GridWidth, int32 _GridHeight);

	EOccupancyState GetTileOccupancyState(FIntVector2 Coord);

	void SetTileOccupancyState(FIntVector2 Coord, EOccupancyState State);
	
private:
	bool IndexIsValid(FIntVector2 Coord);
	
	int32 GridWidth = 0;
	int32 GridHeight = 0;

	OccupancyMatrix Map;
};
