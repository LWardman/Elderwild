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
	void TransferItemToOtherInventory(UInventoryComponent* OtherInventory, UItemDataAsset* Item, int32 Count);
	
	void AddItem(UItemDataAsset* Item, int32 Count);
	void SubtractItem(UItemDataAsset* Item, int32 Count);

	bool HasEnoughOfAnItem(UItemDataAsset* Item, int32 Count);

	void LogInventory();

	const TMap<UItemDataAsset*, int32>& GetInventory() const { return Inventory; }
	
	int32 GetAmountOfDucats() const { return Ducats; }

	void AddDucats(int32 Amount) { Ducats += Amount; }
	void SubtractDucats(int32 Amount) { Ducats -= Amount; }

	bool CanAffordPurchase(int32 PurchaseCost) const { return GetAmountOfDucats() >= PurchaseCost; }	
	void MakePurchase(int32 PurchaseCost);
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Contents")
	TMap<UItemDataAsset*, int32> Inventory;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Currency")
	int32 Ducats = 500;
};
