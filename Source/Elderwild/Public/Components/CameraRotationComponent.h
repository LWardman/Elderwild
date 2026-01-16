#pragma once

#include "Player/Input/DraggingMousePositions.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CameraRotationComponent.generated.h"

class UCameraComponent;

UCLASS(ClassGroup=Camera)
class ELDERWILD_API UCameraRotationComponent : public USceneComponent
{
    GENERATED_BODY()

public:
	UCameraRotationComponent();
	
	void Init(UCameraComponent* InCamera) { Camera = InCamera; }

	void DragRotate(FVector2d Cursor);

	void BeginDragRotate(FVector2d Cursor) { DragRotation.ResetToCursorsPosition(Cursor); }

	void RotateAroundYawAxis(float RotationDirection);
	
private:
	FVector UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float RotationSpeed = 30.f;

	FDraggingMousePositions DragRotation;

	UPROPERTY(Transient)
	UCameraComponent* Camera;
};