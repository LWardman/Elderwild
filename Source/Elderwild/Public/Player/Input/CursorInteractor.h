#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CursorInteractor.generated.h"

class AGrid;
class UMouseMode;
class UMouseModeWidget;

// TODO : is there a point to having this class anymore?
UCLASS()
class ELDERWILD_API UCursorInteractor : public UActorComponent
{
	GENERATED_BODY()

public:
	void Initialize(APlayerController* InController, AGrid* InGrid);

	void UpdateHover();
	void HandleClick();

	void ChangeMouseMode(TSubclassOf<UMouseMode> ModeClass);

private:
	UPROPERTY()
	APlayerController* Controller;

	UPROPERTY()
	AGrid* Grid;

	UPROPERTY()
	UMouseMode* MouseMode;

	void CreateMouseModeWidget();

	UPROPERTY()
	UMouseModeWidget* MouseModeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UMouseModeWidget> MouseModeWidgetClass;
};
