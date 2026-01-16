#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuildingData.generated.h"

class ABuilding;

UCLASS()
class ELDERWILD_API UBuildingData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FIntVector2 BuildingSize = FIntVector2(1, 1);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> BuildingClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> OpaqueBuildingClass;
	
	UPROPERTY(EditAnywhere)
	FText DisplayName;
	
	UPROPERTY(EditAnywhere)
	int32 Cost;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	
	UPROPERTY(EditAnywhere)
	bool bUnlocked = true;
};
