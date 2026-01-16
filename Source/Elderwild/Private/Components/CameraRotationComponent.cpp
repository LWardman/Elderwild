#include "Components/CameraRotationComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"
#include "Logging/ControlsLog.h"

UCameraRotationComponent::UCameraRotationComponent()
{
	DragRotation.Sensitivity = 0.8f;
}

void UCameraRotationComponent::DragRotate(FVector2d Cursor)
{
    FVector MouseDeltaPosition = UpdateMousePositionsAndGetDelta(DragRotation, Cursor);
    const float RotationMagnitude = DragRotation.Sensitivity * MouseDeltaPosition.X;
    RotateAroundYawAxis(RotationMagnitude);
}

void UCameraRotationComponent::RotateAroundYawAxis(float RotationDirection)
{
	if (!Camera)
	{
		UE_LOG(ControlsLog, Warning, TEXT("Camera wasn't found to rotate"));
		return;
	}

	FRotator Rotation = Camera->GetComponentRotation();
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float RotationMagnitude = DeltaTime * RotationSpeed * RotationDirection;
	Rotation.Yaw += RotationMagnitude;
	Camera->SetWorldRotation(Rotation);
}

FVector UCameraRotationComponent::UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor)
{
	CursorPositions.UpdateCurrentPositionToCursor(Cursor);
	const FVector MouseDeltaPosition = CursorPositions.CalculateDeltaVector();
	CursorPositions.UpdateBeginningPositionToCursor(Cursor);

	return MouseDeltaPosition;
}
