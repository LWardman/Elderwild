#include "Creatures/Trader/TradeWidget.h"

#include "Components/Button.h"
#include "Components/InventoryComponent.h"
#include "Components/TileView.h"
#include "Inventory/InventoryItemStack.h"

bool UTradeWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (CloseWidgetButton)
	{
		CloseWidgetButton->OnClicked.AddDynamic(this, &UTradeWidget::CloseWidgetButtonClicked);
	}
	return true;
}

void UTradeWidget::InitializeInventories(UInventoryComponent* TradersInventory, UInventoryComponent* PlayersInventory)
{
	TraderInventory = TradersInventory;
	PlayerInventory = PlayersInventory;
}

void UTradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateInventoryBoxes(TraderInventory, TraderInventoryDisplay);
	CreateInventoryBoxes(PlayerInventory, PlayerInventoryDisplay);
}

void UTradeWidget::CloseWidgetButtonClicked()
{
	EndInteraction.Broadcast();
}

void UTradeWidget::CreateInventoryBoxes(UInventoryComponent* InventoryComp, UTileView* TileView)
{
	if (!InventoryComp || !TileView) return;

	InventoryComp->LogInventory();

	TArray<UObject*> Entry;
	Entry.Reserve(InventoryComp->GetInventory().Num());
	
	for (const auto& InventorySlot : InventoryComp->GetInventory())
	{
		UInventoryItemStack* Stack = NewObject<UInventoryItemStack>(this);
		Stack->Item = InventorySlot.Key;
		Stack->Count = InventorySlot.Value;
		Entry.Add(Stack);
	}

	TileView->ClearListItems();
	TileView->SetListItems(Entry);
}