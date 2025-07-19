#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BuildingDirection.generated.h"

UENUM(BlueprintType)
enum class ECompassDirection : uint8 {
	North UMETA(DisplayName = "North"),
	East  UMETA(DisplayName = "East"),
	South UMETA(DisplayName = "South"),
	West  UMETA(DisplayName = "West"),                  
	COUNT UMETA(Hidden)
};

UCLASS()
class ELDERWILD_API UBuildingDirection : public UObject
{
	GENERATED_BODY()

public:
	static ECompassDirection GetDirection() {return Direction;}

	static void RotateClockwise();

	static FRotator DirectionToRotator(ECompassDirection Direction);

	static FVector2D CentreOffsetMultiplier(FVector2D Offset, ECompassDirection Direction);

private:
	static ECompassDirection Direction;
	
	static uint8 GetNextDirectionIndex();
};
