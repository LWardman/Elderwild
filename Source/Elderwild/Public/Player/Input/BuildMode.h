#pragma once

#include "CoreMinimal.h"
#include "Player/Input/MouseMode.h"
#include "BuildMode.generated.h"

UCLASS()
class ELDERWILD_API UBuildMode : public UMouseMode
{
	GENERATED_BODY()

public:
	virtual void OnMouseModeEnter() override;
	virtual void Click() override;
	virtual void Hover() override;
	virtual void OnMouseModeExit() override;
};
