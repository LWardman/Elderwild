#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Calendar.generated.h"

class USeasonCycler;
class ADirectionalLight;

// TODO : create link between this and the suns position in the engine.
UCLASS()
class ELDERWILD_API UCalendar : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCalendar();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	USeasonCycler* SeasonCycler = nullptr;

	UPROPERTY()
	ADirectionalLight* Sunlight = nullptr;

	TArray<AActor*> GetActorsWithSunTag();

	ADirectionalLight* SearchArrayForDirectionalLight(TArray<AActor*> SunActors);

	void SetSunPositionInSky();
};
