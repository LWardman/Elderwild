#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Calendar.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDERWILD_API UCalendar : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCalendar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
