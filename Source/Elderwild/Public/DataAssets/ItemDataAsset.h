#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

UCLASS()
class ELDERWILD_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Variables")
	FString Name = TEXT("UninitializedName");

	UPROPERTY(EditAnywhere, Category="Variables")
	int32 ItemValue = 0;
	
	UPROPERTY(EditAnywhere, Category="Variables")
	TSoftObjectPtr<UTexture> InventoryIcon;
};
