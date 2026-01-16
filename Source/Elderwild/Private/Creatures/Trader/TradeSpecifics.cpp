#include "Creatures/Trader/TradeSpecifics.h"

#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

#include "Components/IntTextBox.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/InventoryItemStack.h"
#include "Creatures/Trader/TradeWidget.h"
#include "Inventory/ItemDataAsset.h"

TWeakObjectPtr<UTradeSpecifics> UTradeSpecifics::ActiveWidget;
TPair<UInventoryComponent*, UInventoryComponent*> UTradeSpecifics::Traders;

bool UTradeSpecifics::Initialize()
{
	if (!Super::Initialize()) return false;

	if (CancelTradeButton)
		CancelTradeButton->OnReleased.AddDynamic(this, &UTradeSpecifics::SafeCloseWidget);
	
	if (ConfirmTradeButton)
		ConfirmTradeButton->OnReleased.AddDynamic(this, &UTradeSpecifics::OnTradeCompleted);
	
	return true;
}

void UTradeSpecifics::InitializeWithInventoryStack(UInventoryItemStack* Stack)
{
	if (!Stack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Initialized with a nullptr"));
		return;
	}

	ItemStack = Stack;
	
	if (ResourceIcon)
		ResourceIcon->SetBrushFromTexture(nullptr, true);
		SetStackIcon(Stack);	
	
	if (TradeCount)
	{
		TradeCount->SetMinValue(0.0f);
		TradeCount->SetMaxValue(Stack->Count);
		TradeCount->SetStepSize(1.0f);
		TradeCount->MouseUsesStep = true;
		TradeCount->OnValueChanged.AddDynamic(this, &UTradeSpecifics::OnSliderChange);
	}
	if (SellerCount)
		SellerCount->SetIntText(Stack->Count);

	if (BuyerCount)
		BuyerCount->SetIntText(0);
	
	if (TotalCost)
		TotalCost->SetIntText(0);
}

void UTradeSpecifics::SetTraders(UInventoryComponent* PlayerInv, UInventoryComponent* TraderInv)
{
	Traders = TPair<UInventoryComponent*, UInventoryComponent*>(PlayerInv, TraderInv);
}

void UTradeSpecifics::ResetTraders()
{
	Traders = TPair<UInventoryComponent*, UInventoryComponent*>(nullptr, nullptr);
}

void UTradeSpecifics::SetStackIcon(const UInventoryItemStack* Stack)
{
	if (Stack->Item && ResourceIcon)
	{
		if (UTexture* Tex = Stack->Item->InventoryIcon.LoadSynchronous())
		{
			if (auto* Tex2D = Cast<UTexture2D>(Tex))
			{
				ResourceIcon->SetBrushFromTexture(Tex2D, true);
			}
			else
			{
				FSlateBrush B;
				B.SetResourceObject(Tex);
				ResourceIcon->SetBrush(B);
			}
		}
	}		
}

void UTradeSpecifics::OnSliderChange(float InValue)
{
	if (BuyerCount)
		BuyerCount->SetIntText(InValue);
	
	if (ItemStack && SellerCount)
		SellerCount->SetIntText(ItemStack->Count - InValue);

	if (ConfirmTradeButton)
		ConfirmTradeButton->SetIsEnabled( TradeIsValid(InValue) );

	if (TotalCost && ItemStack && ItemStack->Item)
	{
		int32 PurchaseCost = ItemStack->Item->ItemValue * InValue;
		if (UInventoryComponent* Seller = ItemStack->OwnerInventory)
			PurchaseCost *= Seller->GetTradeMultiplier();
		TotalCost->SetIntText(PurchaseCost);
	}
}

bool UTradeSpecifics::TradeIsValid(float NumberOfUnits)
{
	if (!ItemStack || !ItemStack->Item || !ItemStack->OwnerInventory) return false;

	UInventoryComponent* Seller = ItemStack->OwnerInventory;
	int32 PurchaseCost = ItemStack->Item->ItemValue * NumberOfUnits;

	if (Traders.Key && Traders.Value)
	{
		UInventoryComponent* Buyer = (Traders.Key == Seller) ? Traders.Value : Traders.Key;
		PurchaseCost *= Seller->GetTradeMultiplier();
		return Buyer->CanAffordPurchase(PurchaseCost);
	}
	
	return false;
}

void UTradeSpecifics::OnTradeCompleted()
{
	float BuyingQuantity = GetSliderValue();
	
	if (ItemStack)
		ItemStack->Trade.Broadcast(ItemStack, BuyingQuantity);
	
	SafeCloseWidget();	
}

float UTradeSpecifics::GetSliderValue()
{
	return TradeCount ? TradeCount->GetValue() : 0.0f;
}

void UTradeSpecifics::SafeCloseWidget()
{
	ResetTradeSpecifics();
	RemoveFromParent();
}
