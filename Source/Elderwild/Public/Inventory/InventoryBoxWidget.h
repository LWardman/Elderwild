#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "InventoryBoxWidget.generated.h"

class UInventoryItemStack;

UCLASS()
class ELDERWILD_API UInventoryBoxWidget
	: public UUserWidget
	, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ResourceIcon;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResourceCount;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

private:
	void SetStackIcon(const UInventoryItemStack* Stack);
	void SetStackCount(const UInventoryItemStack* Stack);

	UPROPERTY()
	UInventoryItemStack* ItemStack;

	UFUNCTION()
	void OpenTradeSpecificsUI();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), Category = "Trading")
	TSubclassOf<class UTradeSpecifics> TradeSpecificsClass;

	UPROPERTY()
	UTradeSpecifics* TradeSpecificsWidget;
};
