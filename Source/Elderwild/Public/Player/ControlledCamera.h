#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ControlledCamera.generated.h"

struct FCameraBoundaries
{
	FVector Min;
	FVector Max;
};

class UCameraZoomComponent;
class UCameraRotationComponent;
class UCameraTranslationComponent;

UCLASS()
class ELDERWILD_API UControlledCamera : public UCameraComponent
{
	GENERATED_BODY()

public:
	UControlledCamera();

protected:
	virtual void BeginPlay() override;
	
public:
	FCameraBoundaries GetCameraBoundaries() const { return CameraBoundaries; }
	
	void ZoomCamera(float Direction);

	FVector CalculateCameraMovementVectorOnXYPlane(FVector2D PlayerInput) const;
    
	FVector GetForwardXYVector() const;
    
	void BeginDragMovement(FVector2D Cursor);
	
	void DragMove(FVector2d Cursor);

	void BeginDragRotate(FVector2d Cursor);
	void DragRotate(FVector2d Cursor);
	
	void RotateAroundYawAxis(float RotationDirection);

private:
	FCameraBoundaries CameraBoundaries;

	// TODO : Make these components general. For example the CameraRotation class now is bound to it's parent being a camera, this component should work with any class.
	UPROPERTY(EditAnywhere, Category="Camera", meta=(AllowPrivateAccess))
	UCameraZoomComponent* CameraZoom;

	UPROPERTY(EditAnywhere, Category="Camera", meta=(AllowPrivateAccess))
	UCameraRotationComponent* CameraRotation;

	UPROPERTY(EditAnywhere, Category="Camera", meta=(AllowPrivateAccess))
	UCameraTranslationComponent* CameraTranslation;
};
