#pragma once

#include "Player/Input/DraggingMousePositions.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ControlledCamera.generated.h"

struct FCameraBoundaries
{
	FVector Min;
	FVector Max;
};

UCLASS()
class ELDERWILD_API UControlledCamera : public UCameraComponent
{
	GENERATED_BODY()

public:
	UControlledCamera();

protected:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	FCameraBoundaries GetCameraBoundaries() const {return CameraBoundaries;}
	
	void ZoomCamera(float Direction);

	FVector CalculateCameraMovementVectorOnXYPlane(FVector2D PlayerInput) const;
    
	FVector GetForwardXYVector() const;
    
	void RotateAroundYawAxis(float RotationDirection);

	void BeginDragMovement(FVector2D Cursor);

	void DragMove(FVector2d Cursor);

	void BeginDragRotate(FVector2d Cursor);

	void DragRotate(FVector2d Cursor);

	FVector UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float RotationSpeed = 30.f;
	
	FCameraBoundaries CameraBoundaries;
	
	float FieldOfView = 80;
	float TargetFieldOfView = FieldOfView;
	float MinimumFieldOfView = 16.0f;
	float MaximumFieldOfView = 90.0f;

	void InterpolateCameraFieldOfView(float DeltaTime);

	FDraggingMousePositions DragMovement;
	FDraggingMousePositions DragRotation;
};
