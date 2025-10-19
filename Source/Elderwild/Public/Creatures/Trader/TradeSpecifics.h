#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeSpecifics.generated.h"

class UInventoryItemStack;
class UInventoryComponent;
class UButton;
class USlider;
class UTextBlock;
class UIntTextBox;
class UImage;

UCLASS()
class ELDERWILD_API UTradeSpecifics : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void InitializeWithInventoryStack(UInventoryItemStack* Stack);
	
	static void SetTradeSpecifics(UTradeSpecifics* NewWidget) { ActiveWidget = NewWidget; }
	static void ResetTradeSpecifics() { ActiveWidget.Reset(); }
	static bool TradeSpecificsExists() { return ActiveWidget.IsValid(); }

	static void SetTraders(UInventoryComponent* PlayerInv, UInventoryComponent* TraderInv);
	static void ResetTraders();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* CancelTradeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmTradeButton;
	
	UPROPERTY(meta = (BindWidget))
	USlider* TradeCount;
	
	UPROPERTY(meta = (BindWidget))
	UIntTextBox* SellerCount;
	
	UPROPERTY(meta = (BindWidget))
	UIntTextBox* BuyerCount;
	
	UPROPERTY(meta = (BindWidget))
	UImage* ResourceIcon;

	UPROPERTY(meta = (BindWidget))
	UIntTextBox* TotalCost;
	
private:
	UPROPERTY()
	UInventoryItemStack* ItemStack;
	
	void SetStackIcon(const UInventoryItemStack* Stack);

	UFUNCTION()
	void OnSliderChange(float InValue);

	bool TradeIsValid(float NumberOfUnits);

	UFUNCTION()
	void OnTradeCompleted();

	float GetSliderValue();

	UFUNCTION()
	void SafeCloseWidget();
	
	static TWeakObjectPtr<UTradeSpecifics> ActiveWidget;

	static TPair<UInventoryComponent*, UInventoryComponent*> Traders;
};