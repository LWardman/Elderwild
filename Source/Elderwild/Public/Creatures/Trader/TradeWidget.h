#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeWidget.generated.h"

class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndInteraction);

UCLASS()
class ELDERWILD_API UTradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FEndInteraction EndInteraction;
	
	virtual bool Initialize() override;

	void InitializeInventories(UInventoryComponent* TradersInventory, UInventoryComponent* PlayersInventory);

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseWidgetButton;

	UPROPERTY(meta = (BindWidget))
	class UTileView* TraderInventoryDisplay;
	
	UPROPERTY(meta = (BindWidget))
	class UTileView* PlayerInventoryDisplay;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void CloseWidgetButtonClicked();

private:
	UPROPERTY()
	UInventoryComponent* TraderInventory;
	
	UPROPERTY()
	UInventoryComponent* PlayerInventory;

	void CreateInventoryBoxes(UInventoryComponent* InventoryComp, UTileView* TileView);
};
