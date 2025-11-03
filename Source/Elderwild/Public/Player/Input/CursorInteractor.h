#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/Input/MouseModeTypes.h"
#include "CursorInteractor.generated.h"


class AGrid;
class UMouseMode;
class UMouseModeWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseModeChanged, UMouseMode*, MouseMode);

UCLASS()
class ELDERWILD_API UCursorInteractor : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnMouseModeChanged OnMouseModeChanged;
	
	void Initialize(APlayerController* InController, AGrid* InGrid);

	void UpdateHover();
	void HandleClick();

	void ChangeMouseMode(EMouseModeType ModeType);

	UMouseMode* GetMouseMode() const { return MouseMode; }

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
