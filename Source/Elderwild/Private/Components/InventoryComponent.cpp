#include "Components/InventoryComponent.h"

#include "DataAssets/ItemDataAsset.h"

void UInventoryComponent::AddItem(UItemDataAsset* Item, int32 Count)
{
	if (!Item) return;
	if (Inventory.Contains(Item))
	{
		Inventory[Item] += Count;
	}
	else
	{
		Inventory.Add(Item, Count);
	}
}

void UInventoryComponent::SubtractItem(UItemDataAsset* Item, int32 Count)
{
	if (!Item) return;
	if (Inventory.Contains(Item))
	{
		Inventory[Item] -= Count;

		if (Inventory[Item] == 0)
		{
			Inventory.Remove(Item);
		}
	}
}

bool UInventoryComponent::HasEnoughOfAnItem(UItemDataAsset* Item, int32 Count)
{
	if (!Item || !Inventory.Contains(Item)) return false;
	return Inventory[Item] >= Count;
}

void UInventoryComponent::LogInventory()
{
	UE_LOG(LogTemp, Display, TEXT("============================="));
	UE_LOG(LogTemp, Display, TEXT("Inventory"));
	UE_LOG(LogTemp, Display, TEXT("============================="));
	for (const auto& Elem : Inventory)
	{
		UE_LOG(LogTemp, Display, TEXT("%ix %s"), Elem.Value, *Elem.Key->Name);
	}
	UE_LOG(LogTemp, Display, TEXT("============================="));
}
