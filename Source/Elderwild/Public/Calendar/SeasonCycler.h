#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SeasonCycler.generated.h"


UENUM(BlueprintType)
enum FSeason
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSeasonChangeDelegate, FSeason, NewSeason);

class UDayCycler;
enum FDayNight : int;


UCLASS()
class ELDERWILD_API USeasonCycler : public UObject
{
	GENERATED_BODY()

public:
	USeasonCycler();

	UDayCycler* GetDayCycler();
	
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
	UDayCycler* Day;

	int32 CurrentDay = 1;
	int32 MonthLength = 28;
	
	UPROPERTY(BlueprintAssignable, Category = "Day Events")
	FSeasonChangeDelegate SeasonIsChanging;
};
