#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Calendar.generated.h"

class USeasonCycler;
class ADirectionalLight;
class UCalendarWidget;

enum class ESeason : uint8;
enum class EDayNight : uint8;

UCLASS()
class ELDERWILD_API UCalendar : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCalendar();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	EDayNight GetDayState();

private:
	UPROPERTY()
	USeasonCycler* SeasonCycler = nullptr;

	UPROPERTY()
	ADirectionalLight* Sunlight = nullptr;

	TArray<AActor*> GetActorsWithSunTag();
	ADirectionalLight* SearchArrayForDirectionalLight(TArray<AActor*> SunActors);
	void SetSunPositionInSky();

	UFUNCTION()
	void SendSeasonInfoToUI(ESeason NewSeason);

	UFUNCTION()
	void SendDayInfoToUI();
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="CalendarVariables")
	float DayTimeLength = 15.0f;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="CalendarVariables")
	float NightLength = 15.0f;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess), Category="CalendarVariables")
	int32 MonthLength = 7;
	
	void SendTimeInfoToUI();

	UPROPERTY()
	UCalendarWidget* CalendarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UCalendarWidget> CalendarWidgetClass;
};
