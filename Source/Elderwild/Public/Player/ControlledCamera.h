#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ControlledCamera.generated.h"

struct FCameraBoundaries
{
	FVector Min = FVector::ZeroVector;
	FVector Max = FVector::ZeroVector;
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
	FCameraBoundaries GetCameraBoundaries() {return CameraBoundaries;}
	
	void ZoomCamera(float Direction);

	FVector CalculateCameraMovementVectorOnXYPlane(FVector2D PlayerInput) const;
    
	FVector GetForwardXYVector() const;
    
	void RotateAroundYawAxis(float RotationMagnitude);
	
private:
	FCameraBoundaries CameraBoundaries;
	
	float FieldOfView = 80;
	float TargetFieldOfView = FieldOfView;
	float MinimumFieldOfView = 16.0f;
	float MaximumFieldOfView = 90.0f;

	void InterpolateCameraFieldOfView(float DeltaTime);
};
