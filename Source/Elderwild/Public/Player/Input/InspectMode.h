#pragma once

#include "CoreMinimal.h"
#include "Player/Input/MouseMode.h"
#include "InspectMode.generated.h"


UCLASS()
class ELDERWILD_API UInspectMode : public UMouseMode
{
	GENERATED_BODY()

public:
	virtual void Init(APlayerController* InController, AGrid* InGrid) override;
	virtual void Click() override;
	virtual void Hover() override;
};
