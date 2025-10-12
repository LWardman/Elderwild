#include "Inventory/InventoryItemStack.h"

UInventoryItemStack* UInventoryItemStack::Create(UObject* Outer,
												UItemDataAsset* InItem,
												int32 InCount,
												UInventoryComponent* InOwner)
{
	UInventoryItemStack* NewStack = NewObject<UInventoryItemStack>(Outer);
	if (!NewStack) return nullptr;

	NewStack->Item = InItem;
	NewStack->Count = InCount;
	NewStack->OwnerInventory = InOwner;

	return NewStack;
}


