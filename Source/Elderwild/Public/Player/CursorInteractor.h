#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CursorInteractor.generated.h"

class AGrid;
class ACameraController;

UENUM()
enum class FMouseMode
{
	DEFAULT,
	BUILDING
};

UCLASS()
class ELDERWILD_API UCursorInteractor : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(ACameraController* InController, AGrid* InGrid);

	void UpdateHover();
	void HandleClick();

	void ChangeMouseMode(FMouseMode NewMouseMode);

private:
	UPROPERTY()
	ACameraController* Controller;

	UPROPERTY()
	AGrid* Grid;

	UPROPERTY()
	FMouseMode MouseMode = FMouseMode::BUILDING;

	void ClickedInDefaultMode();

	void ClickedInBuildMode();
};
