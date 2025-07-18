#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuildingData.generated.h"

UCLASS()
class ELDERWILD_API UBuildingData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FIntVector2 BuildingSize;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABuilding> BuildingClass;
};
