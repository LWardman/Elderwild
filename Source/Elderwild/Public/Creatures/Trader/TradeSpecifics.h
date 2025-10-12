#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradeSpecifics.generated.h"

class UInventoryItemStack;
class UButton;
class USlider;
class UTextBlock;
class UIntTextBox;

UCLASS()
class ELDERWILD_API UTradeSpecifics : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void InitializeWithInventoryStack(const UInventoryItemStack* Stack);
	
	static void SetTradeSpecifics(UTradeSpecifics* NewWidget) { ActiveWidget = NewWidget; }
	static void ResetTradeSpecifics() { ActiveWidget.Reset(); }
	static bool TradeSpecificsExists() { return ActiveWidget.IsValid(); }
	
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
	
private:
	UPROPERTY()
	UInventoryItemStack* ItemStack;

	UFUNCTION()
	void OnSliderChange(float InValue);

	UFUNCTION()
	void OnTradeCompleted();

	float GetSliderValue();

	UFUNCTION()
	void SafeCloseWidget();
	
	static TWeakObjectPtr<UTradeSpecifics> ActiveWidget;
};