#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuildMenuTabData.generated.h"

class UBuildingData;

UCLASS()
class ELDERWILD_API UBuildMenuTabData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FText TabDisplayName;
	
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UBuildingData>> BuildingTabData;
};
