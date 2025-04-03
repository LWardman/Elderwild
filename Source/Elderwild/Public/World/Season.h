#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Season.generated.h"

class UDay;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSeasonChangeDelegate);

UENUM(BlueprintType)
enum FSeason
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER
};

UCLASS()
class ELDERWILD_API USeason : public UObject
{
	GENERATED_BODY()

public:
	USeason();

private:
	UFUNCTION()
	void OnDayChange();

	FSeason CurrentSeason = SPRING;

	UFUNCTION()
	FSeason GetNextSeason();
	
	UPROPERTY()
	UDay* Day;

	int32 CurrentDay = 1;
	int32 MonthLength = 28;

	int32 GetNumberOfDaysLeft();

	bool IsLastDayOfMonth();
	
	UPROPERTY(BlueprintAssignable, Category = "Day Events")
	FSeasonChangeDelegate SeasonIsChanging;
};
