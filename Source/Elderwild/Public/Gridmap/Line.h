#pragma once

#include "CoreMinimal.h"
#include "Line.generated.h"

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()
	
	UPROPERTY()
	FVector Start;

	UPROPERTY()
	FVector End;
};