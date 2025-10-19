#pragma once

#include "CoreMinimal.h"
#include "Creatures/Creature.h"
#include "Trader.generated.h"

class UFacingWidgetComponent;
class UTradeWidget;
class UMouseMode;

UCLASS()
class ELDERWILD_API ATrader : public ACreature
{
	GENERATED_BODY()
public:
	ATrader();

	UPROPERTY(EditAnywhere, Category="Trading")
	class UInventoryComponent* InventoryComponent;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Indicator")
	UFacingWidgetComponent* Icon;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="UI")
	TSubclassOf<UTradeWidget> TradeWidgetClass;

	UPROPERTY()
	UTradeWidget* TradeWidget;
	
	UFUNCTION()
	void BeginTraderInteraction(AActor* Actor, FKey Key);

	TWeakObjectPtr<UMouseMode> MouseMode;
	bool PlayerIsInInspectMode() const;
	void FetchAndSubscribeToMouseEvents();

	UFUNCTION()
	void OnMouseModeChanged(UMouseMode* NewMouseMode);
};
