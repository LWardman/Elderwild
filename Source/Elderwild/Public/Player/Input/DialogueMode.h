#pragma once

#include "CoreMinimal.h"
#include "Player/Input/MouseMode.h"
#include "DialogueMode.generated.h"


UCLASS()
class ELDERWILD_API UDialogueMode : public UMouseMode
{
	GENERATED_BODY()

public:
	virtual void Init(APlayerController* InController, AGrid* InGrid) override;
	virtual void Click() override;
	virtual void Hover() override {}
	virtual void BeginDestroy() override;
};
