#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/Input/MouseModeTypes.h"
#include "CursorInteractor.generated.h"

class AGrid;
class UMouseMode;
class UMouseModeWidget;

UCLASS()
class ELDERWILD_API UCursorInteractor : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	void UpdateHover();
	void HandleClick();

	void ChangeMouseMode(EMouseModeType ModeType);

	UMouseMode* GetMouseMode() const { return MouseMode; }

private:
	UPROPERTY()
	UMouseMode* MouseMode;

	void CreateMouseModeWidget();

	UPROPERTY()
	UMouseModeWidget* MouseModeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UMouseModeWidget> MouseModeWidgetClass;
};
