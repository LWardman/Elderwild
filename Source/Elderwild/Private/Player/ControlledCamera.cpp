#include "Player/ControlledCamera.h"

#include "GameModes/DevGameMode.h"
#include "Kismet/GameplayStatics.h"

UControlledCamera::UControlledCamera()
{
	PrimaryComponentTick.bCanEverTick = true;

	DragMovement.Sensitivity = 1.5f;
	DragRotation.Sensitivity = 0.8f;
}

void UControlledCamera::BeginPlay()
{
	Super::BeginPlay();
	SetFieldOfView(FieldOfView);

	if (ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		CameraBoundaries = GameMode->CalculateCameraBoundariesFromGrid();
	}
}

void UControlledCamera::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	InterpolateCameraFieldOfView(DeltaTime);
}

void UControlledCamera::ZoomCamera(float Direction)
{
	TargetFieldOfView -= Direction * 2;
	TargetFieldOfView = FMath::Clamp(TargetFieldOfView, MinimumFieldOfView, MaximumFieldOfView);
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

void UControlledCamera::RotateAroundYawAxis(float RotationDirection)
{
	FRotator Rotation = GetComponentRotation();
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float RotationMagnitude = DeltaTime * RotationSpeed * RotationDirection;
	Rotation.Yaw += RotationMagnitude;
	SetWorldRotation(Rotation);
}

void UControlledCamera::BeginDragMovement(FVector2D Cursor)
{
	DragMovement.ResetToCursorsPosition(Cursor);
}

void UControlledCamera::DragMove(FVector2d Cursor)
{
	FVector MouseDeltaPosition = UpdateMousePositionsAndGetDelta(DragMovement, Cursor);
	MouseDeltaPosition *= -1;
	
	FVector ForwardVectorXY = GetForwardXYVector();
	FVector ForwardMovement = ForwardVectorXY * MouseDeltaPosition.Y * DragMovement.Sensitivity;

	FVector RightVector = GetRightVector();
	FVector SidewaysMovement = -1 * RightVector * MouseDeltaPosition.X * DragMovement.Sensitivity;

	FVector CurrentLocation = GetComponentLocation();

	FVector NewLocation = CurrentLocation + ForwardMovement + SidewaysMovement;
	
	SetWorldLocation(NewLocation);
}

void UControlledCamera::BeginDragRotate(FVector2d Cursor)
{
	DragRotation.ResetToCursorsPosition(Cursor);
}

void UControlledCamera::DragRotate(FVector2d Cursor)
{
	FVector MouseDeltaPosition = UpdateMousePositionsAndGetDelta(DragRotation, Cursor);
	const float RotationMagnitude = DragRotation.Sensitivity * MouseDeltaPosition.X;
	RotateAroundYawAxis(RotationMagnitude);
}

FVector UControlledCamera::UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor)
{
	CursorPositions.UpdateCurrentPositionToCursor(Cursor);
	const FVector MouseDeltaPosition = CursorPositions.CalculateDeltaVector();
	CursorPositions.UpdateBeginningPositionToCursor(Cursor);

	return MouseDeltaPosition;
}

void UControlledCamera::InterpolateCameraFieldOfView(float DeltaTime)
{
	const float DifferenceBetweenTargetAndActualFieldOfView = TargetFieldOfView - FieldOfView;
	const float InterpSpeed = FMath::Abs(DifferenceBetweenTargetAndActualFieldOfView);
	FieldOfView = FMath::FInterpTo(FieldOfView, TargetFieldOfView, DeltaTime, InterpSpeed);
	SetFieldOfView(FieldOfView);
}
