#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ElderwildController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UControlledCamera;
class UFloatingPawnMovement;
class AGrid;

/** Controller intended only for use with the player pawn
 */
UCLASS()
class ELDERWILD_API AElderwildController : public APlayerController
{
	GENERATED_BODY()

public:
	AElderwildController();

	UPROPERTY()
	UFloatingPawnMovement* Movement;

	UPROPERTY()
	UControlledCamera* CameraComponent;

	UPROPERTY()
	AGrid* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_StandardPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IA_Click;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IA_Rotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
    UInputAction* IA_Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IA_DragMoveCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IA_DragRotateCamera;

protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	void SetAndCheckPointers();

// =========== Clicking & Hovering ==================
	void OnClickStarted();

	void HandleCursor();

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
	FVector BeginningMousePositionRotate = FVector::ZeroVector;
	FVector CurrentMousePositionRotate = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float RotationSpeed = 30.f;

	void UpdateVariablesWithCursorPosition(FVector& BeginningPosition, FVector& CurrentPosition);

	FVector UpdateMousePositionsAndGetDelta(FVector& BeginningPosition, FVector& CurrentPosition, const FVector2d Cursor);
};
