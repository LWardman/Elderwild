#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ElderwildsCamera.generated.h"


UCLASS()
class ELDERWILD_API UElderwildsCamera : public UCameraComponent
{
	GENERATED_BODY()

public:
	UElderwildsCamera();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;

public:
	void ZoomCamera(float Direction);

private:
	float FieldOfView = 80;
	float TargetFieldOfView = FieldOfView;
	float MinimumFieldOfView = 16.0f;
	float MaximumFieldOfView = 90.0f;

	void InterpolateCameraFieldOfView(float DeltaTime);

public:
	FVector CalculateCameraMovementVectorOnXYPlane(FVector2D PlayerInput) const;

	FVector GetForwardXYVector() const;

	void RotateAroundYawAxis(float RotationMagnitude);
};
