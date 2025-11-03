#include "Inventory/InventoryBoxWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Inventory/InventoryComponent.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "Brushes/SlateColorBrush.h"
#include "Styling/SlateBrush.h"

#include "Components/IntTextBox.h"
#include "DataAssets/ItemDataAsset.h"
#include "Inventory/InventoryItemStack.h"
#include "Creatures/Trader/TradeSpecifics.h"

void UInventoryBoxWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UE_LOG(LogTemp, Display, TEXT("Building a new inventory item.."));
	if (ResourceIcon)  ResourceIcon->SetBrushFromTexture(nullptr, true);
	if (ResourceCount) ResourceCount->SetText(FText::GetEmpty());
	if (UnitValue) UnitValue->SetText(FText::GetEmpty());

	if (UInventoryItemStack* Stack = Cast<UInventoryItemStack>(ListItemObject))
	{
		ItemStack = Stack;
		SetStackIcon(Stack);	
		SetStackCount(Stack);
		SetStackUnitValue(Stack);
		
		if (Button)
		{
			Button->OnReleased.Clear();
			if (ItemStack && ItemStack->Item)
			{
				Button->OnReleased.AddDynamic(this, &UInventoryBoxWidget::OpenTradeSpecificsUI);
			}
			else
			{
				Button->SetIsEnabled(false);
			}
		}
	}
}

void UInventoryBoxWidget::SetStackIcon(const UInventoryItemStack* Stack)
{
	if (!ResourceIcon) return;
	
	if (Stack->Item)
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
	else
	{
		static const FSlateColorBrush BlackBrush(FLinearColor::Black);
		ResourceIcon->SetBrush(BlackBrush);
	}
}

void UInventoryBoxWidget::SetStackCount(const UInventoryItemStack* Stack)
{
	if (!ResourceCount) return;
	
	if (Stack)
	{
		ResourceCount->SetText(FText::GetEmpty());

		if (Stack->Count > 0)
			ResourceCount->SetIntText(Stack->Count);
	}
}

void UInventoryBoxWidget::SetStackUnitValue(const UInventoryItemStack* Stack)
{
	if (!UnitValue) return;
	
	if (Stack && Stack->Item && Stack->OwnerInventory)
	{
		UE_LOG(LogTemp, Display, TEXT("Setting stack unit value"));
		int32 ResourceValue = Stack->Item->ItemValue * Stack->OwnerInventory->GetTradeMultiplier(); 
		UnitValue->SetIntText(ResourceValue);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Setting empty stack unit value"));
		UnitValue->SetText(FText::GetEmpty());
	}
}

void UInventoryBoxWidget::OpenTradeSpecificsUI()
{
	UE_LOG(LogTemp, Display, TEXT("Opening trade specifics"));

	if (UTradeSpecifics::TradeSpecificsExists())
	{
		UE_LOG(LogTemp, Display, TEXT("A trade is already in progress, aborting.."));
		return;
	}
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (TradeSpecificsClass && PlayerController)
	{
		TradeSpecificsWidget = CreateWidget<UTradeSpecifics>(PlayerController, TradeSpecificsClass);

		if (TradeSpecificsWidget && ItemStack)
		{
			TradeSpecificsWidget->InitializeWithInventoryStack(ItemStack);
			TradeSpecificsWidget->AddToPlayerScreen();
			UTradeSpecifics::SetTradeSpecifics(TradeSpecificsWidget);
		}
	}
}
