#include "Components\CameraTranslationComponent.h"

UCameraTranslationComponent::UCameraTranslationComponent()
{
	DragTranslation.Sensitivity = 1.5f;
}

void UCameraTranslationComponent::DragMove(FVector2d Cursor)
{
	if (!Camera) return;

	FVector MouseDeltaPosition = UpdateMousePositionsAndGetDelta(DragTranslation, Cursor);
	MouseDeltaPosition *= -1;
	
	FVector ForwardVectorXY = Camera->GetForwardXYVector();
	FVector ForwardMovement = ForwardVectorXY * MouseDeltaPosition.Y * DragTranslation.Sensitivity;

	FVector RightVector = Camera->GetRightVector();
	FVector SidewaysMovement = -1 * RightVector * MouseDeltaPosition.X * DragTranslation.Sensitivity;

	FVector CurrentLocation = Camera->GetComponentLocation();

	FVector NewLocation = CurrentLocation + ForwardMovement + SidewaysMovement;
	
	Camera->SetWorldLocation(NewLocation);
}

void UCameraTranslationComponent::OnRegister()
{
	Super::OnRegister();

	Camera = Cast<UCameraComponent>(GetAttachParent());
}

FVector UCameraTranslationComponent::UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor)
{
	CursorPositions.UpdateCurrentPositionToCursor(Cursor);
	const FVector MouseDeltaPosition = CursorPositions.CalculateDeltaVector();
	CursorPositions.UpdateBeginningPositionToCursor(Cursor);

	return MouseDeltaPosition;
}

