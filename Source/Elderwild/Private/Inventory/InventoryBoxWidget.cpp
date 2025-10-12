#include "Inventory/InventoryBoxWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"

#include "DataAssets/ItemDataAsset.h"
#include "Inventory/InventoryItemStack.h"
#include "Creatures/Trader/TradeSpecifics.h"
#include "Creatures/Trader/TradeWidget.h"

void UInventoryBoxWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UE_LOG(LogTemp, Display, TEXT("Building a new inventory item.."));
	if (ResourceIcon)  ResourceIcon->SetBrushFromTexture(nullptr, true);
	if (ResourceCount) ResourceCount->SetText(FText::GetEmpty());
	if (!ListItemObject) return;

	if (UInventoryItemStack* Stack = Cast<UInventoryItemStack>(ListItemObject))
	{
		ItemStack = Stack;
		SetStackIcon(Stack);	
		SetStackCount(Stack);
	}

	if (Button)
	{
		Button->OnReleased.Clear();
		Button->OnReleased.AddDynamic(this, &UInventoryBoxWidget::OpenTradeSpecificsUI);
	}
}

void UInventoryBoxWidget::SetStackIcon(const UInventoryItemStack* Stack)
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

void UInventoryBoxWidget::SetStackCount(const UInventoryItemStack* Stack)
{
	if (ResourceCount)
		ResourceCount->SetText(FText::AsNumber(Stack->Count));
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
