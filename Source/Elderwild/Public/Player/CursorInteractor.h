#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CursorInteractor.generated.h"

class AGrid;
class UMouseModeWidget;

UENUM()
enum class EMouseMode : uint8
{
	DEFAULT,
	BUILDING
};

UCLASS()
class ELDERWILD_API UCursorInteractor : public UActorComponent
{
	GENERATED_BODY()

public:
	void Initialize(APlayerController* InController, AGrid* InGrid);

	void UpdateHover();
	void HandleClick();

	void ChangeMouseMode(EMouseMode NewMouseMode);

private:
	UPROPERTY()
	APlayerController* Controller;

	UPROPERTY()
	AGrid* Grid;

	UPROPERTY()
	EMouseMode MouseMode = EMouseMode::DEFAULT;

	void ClickedInDefaultMode();

	void ClickedInBuildMode();

	void CreateMouseModeWidget();

	UPROPERTY()
	UMouseModeWidget* MouseModeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UMouseModeWidget> MouseModeWidgetClass;
};
