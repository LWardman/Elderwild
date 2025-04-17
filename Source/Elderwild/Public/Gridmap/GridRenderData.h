#pragma once

#include "CoreMinimal.h"
#include "GridRenderData.generated.h"

USTRUCT(BlueprintType)
struct FGridRenderData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	TArray<int32> Triangles;
};
