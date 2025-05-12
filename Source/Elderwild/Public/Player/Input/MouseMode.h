#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MouseMode.generated.h"

class AGrid;

UCLASS()
class ELDERWILD_API UMouseMode : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init(APlayerController* InController, AGrid* InGrid);
	virtual void Click();
	virtual void Hover();
	virtual void BeginDestroy() override;

	UPROPERTY()
	APlayerController* Controller;

	UPROPERTY()
	AGrid* Grid;
};
