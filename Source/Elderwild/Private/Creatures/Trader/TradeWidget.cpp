#include "Creatures/Trader/TradeWidget.h"

#include "Components/Button.h"
#include "Components/TileView.h"
#include "Kismet/GameplayStatics.h"

#include "Components/IntTextBox.h"
#include "DataAssets/ItemDataAsset.h"
#include "Components/InventoryComponent.h"
#include "Inventory/InventoryItemStack.h"
#include "Creatures/Trader/TradeSpecifics.h"

TWeakObjectPtr<UTradeWidget> UTradeWidget::ActiveWidget;

bool UTradeWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (CloseWidgetButton)
		CloseWidgetButton->OnClicked.AddDynamic(this, &UTradeWidget::CloseWidgetButtonClicked);

	UGameplayStatics::SetGlobalTimeDilation(this, 0.0001f);
	
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

	RefreshInventoryDisplays();
	RefreshDucats();
}

void UTradeWidget::CloseWidgetButtonClicked()
{
	ResetTradeWidget();	
	UGameplayStatics::SetGlobalTimeDilation(this, 1.0f);
	RemoveFromParent();
}

void UTradeWidget::CreateInventoryBoxes(UInventoryComponent* InventoryComp, UTileView* TileView)
{
	if (!InventoryComp || !TileView) return;

	InventoryComp->LogInventory();

	TArray<UObject*> Entry;
	Entry.Reserve(InventoryComp->GetInventory().Num());
	
	for (const auto& InventorySlot : InventoryComp->GetInventory())
	{
		UInventoryItemStack* Stack = UInventoryItemStack::Create(this, InventorySlot.Key, InventorySlot.Value, InventoryComp);
		Stack->Trade.AddDynamic(this, &UTradeWidget::TradeListener);
		Entry.Add(Stack);
	}

	TileView->ClearListItems();
	TileView->SetListItems(Entry);
}

void UTradeWidget::TradeListener(UInventoryItemStack* Stack, int32 Quantity)
{
	UE_LOG(LogTemp, Display, TEXT("Starting trade"));
	if (!Stack || !Stack->Item || Quantity == 0) return;

	UInventoryComponent* Seller = Stack->OwnerInventory;

	UInventoryComponent* Buyer = (Seller == TraderInventory) ? PlayerInventory : TraderInventory;
	if (Buyer && Seller)
	{
		int32 StackCost = Stack->Item->ItemValue * Quantity;
		if (Buyer->CanAffordPurchase(StackCost))
		{
			UE_LOG(LogTemp, Display, TEXT("Transferring Items..."));
			Buyer->MakePurchase(StackCost);
			Seller->AddDucats(StackCost);
			Seller->TransferItemToOtherInventory(Buyer, Stack->Item, Quantity);
			
			RefreshInventoryDisplays();
			RefreshDucats();
		}
	}
}

void UTradeWidget::RefreshDucats()
{
	if (TraderDucats && TraderInventory)
		TraderDucats->SetIntText(TraderInventory->GetAmountOfDucats());
			
	if (PlayerDucats && PlayerInventory)
		PlayerDucats->SetIntText(PlayerInventory->GetAmountOfDucats());
}

void UTradeWidget::RefreshInventoryDisplays()
{
	CreateInventoryBoxes(PlayerInventory, PlayerInventoryDisplay);
	CreateInventoryBoxes(TraderInventory, TraderInventoryDisplay);
}
