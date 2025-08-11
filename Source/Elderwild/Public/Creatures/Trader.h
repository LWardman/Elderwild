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
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Indicator")
	class UFacingWidgetComponent* Icon;
};
