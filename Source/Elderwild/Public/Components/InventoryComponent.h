#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDERWILD_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AddItem(UItemDataAsset* Item, int32 Count);
	void SubtractItem(UItemDataAsset* Item, int32 Count);

	bool HasEnoughOfAnItem(UItemDataAsset* Item, int32 Count);

	void LogInventory();

	const TMap<UItemDataAsset*, int32>& GetInventory() const { return Inventory; }
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Contents")
	TMap<UItemDataAsset*, int32> Inventory;
};
