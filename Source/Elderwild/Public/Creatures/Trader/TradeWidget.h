#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeWidget.generated.h"

class UIntTextBox;
class UInventoryComponent;
class UTileView;
class UItemDataAsset;
class UInventoryItemStack;

UCLASS()
class ELDERWILD_API UTradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void InitializeInventories(UInventoryComponent* TradersInventory, UInventoryComponent* PlayersInventory);

	static void SetTradeWidget(UTradeWidget* NewWidget) { ActiveWidget = NewWidget; }
	static void ResetTradeWidget() { ActiveWidget.Reset(); }
	static bool TradeWidgetExists() { return ActiveWidget.IsValid(); }

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseWidgetButton;

	// TODO : Make this widget summon two inventory display widgets instead
	UPROPERTY(meta = (BindWidget))
	UTileView* TraderInventoryDisplay;
	
	UPROPERTY(meta = (BindWidget))
	UIntTextBox* TraderDucats;
	
	UPROPERTY(meta = (BindWidget))
	UTileView* PlayerInventoryDisplay;
	
	UPROPERTY(meta = (BindWidget))
	UIntTextBox* PlayerDucats;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void CloseWidgetButtonClicked();

private:
	UPROPERTY()
	UInventoryComponent* TraderInventory;
	
	UPROPERTY()
	UInventoryComponent* PlayerInventory;

	void CreateInventoryBoxes(UInventoryComponent* InventoryComp, UTileView* TileView);
	
	UFUNCTION()
	void TradeListener(UInventoryItemStack* Stack, int32 Quantity);

	void RefreshDucats();
	void RefreshInventoryDisplays();

	static TWeakObjectPtr<UTradeWidget> ActiveWidget;
};
