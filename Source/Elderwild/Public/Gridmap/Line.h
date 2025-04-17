#pragma once

#include "CoreMinimal.h"
#include "Line.generated.h"

USTRUCT()
struct FLine
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	FVector Start;

	UPROPERTY()
	FVector End;
};