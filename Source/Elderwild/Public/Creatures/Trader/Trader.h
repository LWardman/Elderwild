#pragma once

#include "CoreMinimal.h"
#include "Creatures/Creature.h"
#include "Trader.generated.h"

UCLASS()
class ELDERWILD_API ATrader : public ACreature
{
	GENERATED_BODY()
public:
	ATrader();

	UPROPERTY(EditAnywhere, Category="Trading")
	class UDucatPouch* DucatPouch;

	UPROPERTY(EditAnywhere, Category="Trading")
	class UInventoryComponent* InventoryComponent;
	

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Indicator")
	class UFacingWidgetComponent* Icon;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="UI")
	TSubclassOf<class UTradeWidget> TradeWidgetClass;

	UPROPERTY()
	UTradeWidget* TradeWidget;

	UFUNCTION()
	void BeginTraderInteraction(AActor* Actor, FKey Key);

	UFUNCTION()
	void EndTraderInteraction();

	bool IsTrading = false;
};
