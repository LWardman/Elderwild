#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ElderwildController.generated.h"

class UFloatingPawnMovement;
class UInputMappingContext;
class UInputAction;
class APlayerPawn;
struct FInputActionValue;

/** Controller intended only for use with the player pawn
 */
UCLASS()
class ELDERWILD_API AElderwildController : public APlayerController
{
	GENERATED_BODY()

public:
	AElderwildController();

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

	UPROPERTY()
	UFloatingPawnMovement* Movement;

protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnClickStarted();

	void MoveCameraOnXYPlane(const FInputActionValue& Value);

	void RotateCameraAroundYawAxis(const FInputActionValue& Value);

	void ZoomCamera(const FInputActionValue& Value);

	void DragMoveCamera(const FInputActionValue& Value);

	void DragRotateCamera(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float RotationSpeed = 10.f;

	float FieldOfView = 90;
	float TargetFieldOfView = FieldOfView;
	float MinimumFieldOfView = 16.0f;
	float MaximumFieldOfView = 90.0f;

	void InterpolateCameraFieldOfView(float DeltaSeconds);

	UPROPERTY()
	APlayerPawn* PlayerPawn;
};
