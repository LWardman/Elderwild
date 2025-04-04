#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Calendar.generated.h"

class USeasonCycler;
class ADirectionalLight;

UCLASS()
class ELDERWILD_API UCalendar : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCalendar();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USeasonCycler* SeasonCycler;

	UPROPERTY()
	ADirectionalLight* Sunlight;
};
