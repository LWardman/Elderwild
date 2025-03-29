#include "Components/ControlledCamera.h"


UControlledCamera::UControlledCamera()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UControlledCamera::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	InterpolateCameraFieldOfView(DeltaTime);
}

void UControlledCamera::BeginPlay()
{
	Super::BeginPlay();
	SetFieldOfView(FieldOfView);
}

void UControlledCamera::ZoomCamera(float Direction)
{
	TargetFieldOfView -= Direction * 2;
	TargetFieldOfView = FMath::Clamp(TargetFieldOfView, MinimumFieldOfView, MaximumFieldOfView);
}

void UControlledCamera::InterpolateCameraFieldOfView(float DeltaTime)
{
	const float DifferenceBetweenTargetAndActualFieldOfView = TargetFieldOfView - FieldOfView;
	const float InterpSpeed = FMath::Abs(DifferenceBetweenTargetAndActualFieldOfView);

	FieldOfView = FMath::FInterpTo(FieldOfView, TargetFieldOfView, DeltaTime, InterpSpeed);

	SetFieldOfView(FieldOfView);
}

FVector UControlledCamera::CalculateCameraMovementVectorOnXYPlane(FVector2D PlayerInput) const
{
	FVector ForwardXY = GetForwardXYVector();
	FVector RightVector = GetRightVector();
	
	return ForwardXY * PlayerInput.X + RightVector * PlayerInput.Y;
}

FVector UControlledCamera::GetForwardXYVector() const 
{
	FVector ForwardVector = GetForwardVector();

	FVector ForwardXY = FVector{ ForwardVector.X, ForwardVector.Y, 0.0f };
	ForwardXY.Normalize();

	return ForwardXY;
}

void UControlledCamera::RotateAroundYawAxis(float RotationMagnitude)
{
	FRotator Rotation = GetComponentRotation();

	Rotation.Yaw += RotationMagnitude;

	SetWorldRotation(Rotation);
}
