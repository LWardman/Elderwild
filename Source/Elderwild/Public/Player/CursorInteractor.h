#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CursorInteractor.generated.h"

class AGrid;
class ACameraController;
class UBuildingModeWidget;

UENUM()
enum class FMouseMode
{
	DEFAULT,
	BUILDING
};

// TODO : this class shouldn't know the internals of AGrid, it should just pass the mouse mode to it.
UCLASS()
class ELDERWILD_API UCursorInteractor : public UActorComponent
{
	GENERATED_BODY()

public:
	void Initialize(ACameraController* InController, AGrid* InGrid);

	void UpdateHover();
	void HandleClick();

	void ChangeMouseMode(FMouseMode NewMouseMode);

private:
	UPROPERTY()
	ACameraController* Controller; // TODO : does this need to be ACameraController? Why not APlayerController?

	UPROPERTY()
	AGrid* Grid;

	UPROPERTY()
	FMouseMode MouseMode = FMouseMode::DEFAULT;

	void ClickedInDefaultMode();

	void ClickedInBuildMode();

	void CreateMouseModeWidget();

	UPROPERTY()
	UBuildingModeWidget* MouseModeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UBuildingModeWidget> MouseModeWidgetClass;
};
