#include "Components/ElderwildsCamera.h"


UElderwildsCamera::UElderwildsCamera()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UElderwildsCamera::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	InterpolateCameraFieldOfView(DeltaTime);
}

void UElderwildsCamera::BeginPlay()
{
	Super::BeginPlay();
	SetFieldOfView(FieldOfView);
}

void UElderwildsCamera::ZoomCamera(float Direction)
{
	TargetFieldOfView -= Direction * 2;
	TargetFieldOfView = FMath::Clamp(TargetFieldOfView, MinimumFieldOfView, MaximumFieldOfView);
}

void UElderwildsCamera::InterpolateCameraFieldOfView(float DeltaTime)
{
	const float DifferenceBetweenTargetAndActualFieldOfView = TargetFieldOfView - FieldOfView;
	const float InterpSpeed = FMath::Abs(DifferenceBetweenTargetAndActualFieldOfView);

	FieldOfView = FMath::FInterpTo(FieldOfView, TargetFieldOfView, DeltaTime, InterpSpeed);

	SetFieldOfView(FieldOfView);
}

FVector UElderwildsCamera::CalculateCameraMovementVectorOnXYPlane(FVector2D PlayerInput) const
{
	FVector ForwardXY = GetForwardXYVector();
	FVector RightVector = GetRightVector();
	
	return ForwardXY * PlayerInput.X + RightVector * PlayerInput.Y;
}

FVector UElderwildsCamera::GetForwardXYVector() const 
{
	FVector ForwardVector = GetForwardVector();

	FVector ForwardXY = FVector{ ForwardVector.X, ForwardVector.Y, 0.0f };
	ForwardXY.Normalize();

	return ForwardXY;
}

void UElderwildsCamera::RotateAroundYawAxis(float RotationMagnitude)
{
	FRotator Rotation = GetComponentRotation();

	Rotation.Yaw += RotationMagnitude;

	SetWorldRotation(Rotation);
}
