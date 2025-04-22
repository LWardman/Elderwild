#pragma once

#include "CoreMinimal.h"
#include "DraggingMousePositions.generated.h"

USTRUCT()
struct FDraggingMousePositions
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector BeginningPosition;

	UPROPERTY()
	FVector CurrentPosition;

	UPROPERTY()
	float Sensitivity = 1.0f;
};
