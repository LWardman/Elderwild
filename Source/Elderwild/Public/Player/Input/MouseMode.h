#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MouseMode.generated.h"

class AGrid;

UCLASS(Abstract)
class ELDERWILD_API UMouseMode : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnMouseModeEnter();
	virtual void Click();
	virtual void Hover();
	virtual void OnMouseModeExit();
	
protected:
	APlayerController* GetController() const;
	AGrid* GetGrid() const;
	FHitResult GetHitResultUnderCursor() const;	
};
