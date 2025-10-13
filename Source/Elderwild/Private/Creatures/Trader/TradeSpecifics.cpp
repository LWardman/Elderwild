#include "Creatures/Trader/TradeSpecifics.h"

#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/IntTextBox.h"
#include "Inventory/InventoryItemStack.h"

#include "Creatures/Trader/TradeWidget.h"

TWeakObjectPtr<UTradeSpecifics> UTradeSpecifics::ActiveWidget;

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
}

void UTradeSpecifics::OnSliderChange(float InValue)
{
	if (BuyerCount)
		BuyerCount->SetIntText(InValue);
	
	if (ItemStack && SellerCount)
		SellerCount->SetIntText(ItemStack->Count - InValue);
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
	RemoveFromParent();
	ResetTradeSpecifics();
}
