#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OccupancyMap.generated.h"

UENUM(BlueprintType)
enum FOccupancyState : uint8
{
	EMPTY,
	OCCUPIED
};

typedef TArray<TArray<FOccupancyState>> OccupancyMatrix;

UCLASS()
class ELDERWILD_API UOccupancyMap : public UObject
{
	GENERATED_BODY()

public:
	void Init(int32 _GridWidth, int32 _GridHeight);

	FOccupancyState GetTileOccupancyState(FIntVector2 Coord);

	void SetTileOccupancyState(FIntVector2 Coord, FOccupancyState State);
	
private:
	bool IndexIsValid(FIntVector2 Coord);
	
	int32 GridWidth;
	int32 GridHeight;

	OccupancyMatrix Map;
};
