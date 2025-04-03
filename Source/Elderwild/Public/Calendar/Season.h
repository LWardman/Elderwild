#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Season.generated.h"


UENUM(BlueprintType)
enum FSeason
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSeasonChangeDelegate, FSeason, NewSeason);

class UDay;
enum FDayNight : int;


UCLASS()
class ELDERWILD_API USeason : public UObject
{
	GENERATED_BODY()

public:
	USeason();

	UDay* GetDayCycler();
	
	int32 GetNumberOfDaysLeft();

	bool IsLastDayOfMonth();

	FSeason GetSeason();

private:
	UFUNCTION()
	void OnDayChange(FDayNight NewState);

	FSeason CurrentSeason = SPRING;

	UFUNCTION()
	FSeason GetNextSeason();

	void ChangeSeason();
	
	UPROPERTY()
	UDay* Day;

	int32 CurrentDay = 1;
	int32 MonthLength = 28;
	
	UPROPERTY(BlueprintAssignable, Category = "Day Events")
	FSeasonChangeDelegate SeasonIsChanging;
};
