#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemStack.generated.h"

class UItemDataAsset;

UCLASS(BlueprintType)
class ELDERWILD_API UInventoryItemStack : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemDataAsset* Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 0;	
};
