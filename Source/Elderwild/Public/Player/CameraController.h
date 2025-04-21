#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UControlledCamera;
class UFloatingPawnMovement;
class AGrid;
class UInputDataConfig;
class UCursorInteractor;

/** Controller intended only for use with the player pawn
 */
UCLASS()
class ELDERWILD_API ACameraController : public APlayerController
{
	GENERATED_BODY()

public:
	ACameraController();

	UPROPERTY()
	UFloatingPawnMovement* Movement;

	UPROPERTY()
	UControlledCamera* CameraComponent;

	UPROPERTY()
	AGrid* Grid;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_StandardPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess = "true"))
	UInputDataConfig* InputActions;

	UPROPERTY()
	UCursorInteractor* CursorInteractor;
	
protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	// TODO : seems like bad design to do this
	void SetAndCheckPointers();

// =========== Clicking & Hovering ==================
	void OnClick();

// =========== Camera Zoom Movement ==================
protected:
	void ZoomCamera(const FInputActionValue& Value);

// =========== Camera Location Movement ==================
	void MoveCameraOnXYPlane(const FInputActionValue& Value);
	
	void BeginDragMoveCamera(const FInputActionValue& Value);
	void DragMoveCamera(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float DragCameraMoveSensitivity = 1.5f;
	FVector BeginningMousePositionMove = FVector::ZeroVector;
	FVector CurrentMousePositionMove = FVector::ZeroVector;

// =========== Camera Rotation Movement ==================	
protected:
	void BeginDragRotatingCamera(const FInputActionValue& Value);
	void DragRotateCamera(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float DragCameraRotateSensitivity = 0.8f;

protected:
	void RotateCameraAroundYawAxis(const FInputActionValue& Value);

private:
	// TODO : DRY with drag rotating camera. Make into a struct?
	FVector BeginningMousePositionRotate = FVector::ZeroVector;
	FVector CurrentMousePositionRotate = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float RotationSpeed = 30.f;

	void UpdateVariablesWithCursorPosition(FVector& BeginningPosition, FVector& CurrentPosition);

	FVector UpdateMousePositionsAndGetDelta(FVector& BeginningPosition, FVector& CurrentPosition, const FVector2d Cursor);
};
