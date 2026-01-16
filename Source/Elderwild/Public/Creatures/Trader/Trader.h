#pragma once

#include "CoreMinimal.h"
#include "Creatures/Creature.h"
#include "Trader.generated.h"

class UFacingWidgetComponent;
class UTradeWidget;
class UMouseMode;
class UInventoryComponent;

UCLASS()
class ELDERWILD_API ATrader : public ACreature
{
	GENERATED_BODY()
public:
	ATrader();

	UPROPERTY(EditAnywhere, Category="Trading")
	UInventoryComponent* InventoryComponent;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Indicator")
	UFacingWidgetComponent* Icon;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="UI")
	TSubclassOf<UTradeWidget> TradeWidgetClass;

	UPROPERTY()
	UTradeWidget* TradeWidget;
	
	UFUNCTION()
	void BeginTraderInteraction(AActor* Actor, FKey Key);

	UFUNCTION()
	void OnMouseModeChanged(UMouseMode* NewMouseMode);
	
	bool bActivatable = true;
};
