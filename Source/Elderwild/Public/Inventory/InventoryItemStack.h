#pragma once

#include "CoreMinimal.h"
#include "InventoryItemStack.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTrade, UInventoryItemStack*, Stack, int32, Quantity);

class UItemDataAsset;
class UInventoryComponent;

UCLASS(BlueprintType)
class ELDERWILD_API UInventoryItemStack : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FTrade Trade;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemDataAsset* Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 0;

	UPROPERTY()
	UInventoryComponent* OwnerInventory = nullptr;

	static UInventoryItemStack* Create(UObject* Outer,
									UItemDataAsset* InItem,
									int32 InCount,
									UInventoryComponent* InOwner);
};

