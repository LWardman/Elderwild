#include "Components/CameraRotationComponent.h"

#include "Kismet/GameplayStatics.h"

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

void UCameraRotationComponent::OnRegister()
{
    Super::OnRegister();

    Camera = Cast<UCameraComponent>(GetAttachParent());
}

void UCameraRotationComponent::RotateAroundYawAxis(float RotationDirection)
{
    if (!Camera) return;

    FRotator Rotation = Camera->GetComponentRotation();
    const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    const float RotationMagnitude = DeltaTime * RotationSpeed * RotationDirection;
    Rotation.Yaw += RotationMagnitude;
    Camera->SetWorldRotation(Rotation);
}

FVector UControlledCamera::UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor)
{
	CursorPositions.UpdateCurrentPositionToCursor(Cursor);
	const FVector MouseDeltaPosition = CursorPositions.CalculateDeltaVector();
	CursorPositions.UpdateBeginningPositionToCursor(Cursor);

	return MouseDeltaPosition;
}
