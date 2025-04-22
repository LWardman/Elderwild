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

	void ResetToCursorsPosition(FVector2D Cursor)
	{
		UpdateCurrentPositionToCursor(Cursor);
		UpdateBeginningPositionToCursor(Cursor);
	}

	void UpdateCurrentPositionToCursor(FVector2D Cursor)
	{
		CurrentPosition = FVector(Cursor.X, Cursor.Y, 0);
	}

	void UpdateBeginningPositionToCursor(FVector2D Cursor)
	{
		BeginningPosition = FVector(Cursor.X, Cursor.Y, 0);
	}

	FVector CalculateDeltaVector()
	{
		return BeginningPosition - CurrentPosition;
	}
};
