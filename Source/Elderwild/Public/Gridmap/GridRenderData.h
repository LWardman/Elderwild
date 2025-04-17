#pragma once

#include "CoreMinimal.h"
#include "GridRenderData.generated.h"

USTRUCT()
struct FGridRenderData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	TArray<int32> Triangles;
};
