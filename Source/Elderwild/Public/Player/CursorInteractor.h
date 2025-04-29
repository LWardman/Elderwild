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
