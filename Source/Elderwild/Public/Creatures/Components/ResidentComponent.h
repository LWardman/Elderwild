#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResidentComponent.generated.h"

class AHouse;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHouseChanged, AHouse*, NewHouse);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDERWILD_API UResidentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FHouseChanged HouseChanged;
	
	void AssignToHouse(AHouse* NewHouse);

	void RemoveFromHouse();

	bool HasHome() const;
	
	FVector GetHomeLocation() const;
	
private:
	UPROPERTY(VisibleAnywhere)
	AHouse* House;
};
