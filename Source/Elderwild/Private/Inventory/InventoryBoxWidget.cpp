#include "Inventory/InventoryBoxWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

#include "DataAssets/ItemDataAsset.h"
#include "Inventory/InventoryItemStack.h"

void UInventoryBoxWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UE_LOG(LogTemp, Display, TEXT("Building a new inventory item.."));
	if (ResourceIcon)  ResourceIcon->SetBrushFromTexture(nullptr, true);
	if (ResourceCount) ResourceCount->SetText(FText::GetEmpty());
	if (!ListItemObject) return;

	if (const UInventoryItemStack* Stack = Cast<UInventoryItemStack>(ListItemObject))
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

		if (ResourceCount)
		{
			ResourceCount->SetText(FText::AsNumber(Stack->Count));
		}

		return;
	}

	if (const UItemDataAsset* Item = Cast<UItemDataAsset>(ListItemObject))
	{
		if (ResourceIcon)
		{
			if (UTexture* Tex = Item->InventoryIcon.LoadSynchronous())
			{
				ResourceIcon->SetBrushFromTexture(Cast<UTexture2D>(Tex), true);
			}
		}
		if (ResourceCount)
		{
			ResourceCount->SetText(FText::AsNumber(1));
		}
	}	
}
