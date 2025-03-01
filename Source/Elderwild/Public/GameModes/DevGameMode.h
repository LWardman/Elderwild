#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevGameMode.generated.h"

class AGrid;

UCLASS()
class ELDERWILD_API ADevGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADevGameMode();

	virtual void BeginPlay() override;

	UPROPERTY()
	AGrid* Grid;

	AGrid* FindGrid();

	AGrid* GetGrid();
};
