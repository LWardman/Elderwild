#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DucatPouch.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDERWILD_API UDucatPouch : public UActorComponent
{
	GENERATED_BODY()

public:
	int32 GetAmountOfDucats() const { return Ducats; }

	void AddDucats(int32 Amount);
	void SubtractDucats(int32 Amount);

	bool CanAffordPurchase(int32 PurchaseCost) const { return GetAmountOfDucats() >= PurchaseCost; }	
	void MakePurchase(int32 PurchaseCost);
	
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="Currency")
	int32 Ducats = 500;
};
