#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SeasonCycler.generated.h"

UENUM(BlueprintType)
enum class ESeason : uint8
{
	Spring	UMETA(DisplayName = "Spring"),
	Summer	UMETA(DisplayName = "Summer"),
	Autumn	UMETA(DisplayName = "Autumn"),
	Winter	UMETA(DisplayName = "Winter")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSeasonChangeDelegate, ESeason, NewSeason);

class UDayCycler;
enum class EDayNight : uint8;

UCLASS()
class ELDERWILD_API USeasonCycler : public UObject
{
	GENERATED_BODY()

public:
	void Init(UDayCycler* DayCycler);

	UDayCycler* GetDayCycler() const;
	
	int32 GetNumberOfDaysLeft() const;
	int32 GetCurrentDay() const {return CurrentDay;}

	bool IsLastDayOfMonth() const;

	ESeason GetSeason() const;

	UPROPERTY(BlueprintAssignable, Category = "Season Events")
	FSeasonChangeDelegate SeasonIsChanging;

private:
	UFUNCTION()
	void OnDayChange(EDayNight NewState);

	ESeason CurrentSeason = ESeason::Spring;

	UFUNCTION()
	ESeason GetNextSeason() const;

	void ChangeSeason();
	
	UPROPERTY()
	UDayCycler* Day;

	int32 CurrentDay = 1;
	int32 MonthLength = 28;
};
