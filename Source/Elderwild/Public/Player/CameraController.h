#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/Input/MouseModeTypes.h"
#include "CameraController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class UControlledCamera;
class UFloatingPawnMovement;
class AGrid;
class UInputDataConfig;
class UCursorInteractor;
class UMouseMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseModeChanged, UMouseMode*, MouseMode);

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

	UPROPERTY(EditAnywhere)
	UCursorInteractor* CursorInteractor;
	
	void ChangeMouseMode(EMouseModeType ModeType);
	const UMouseMode* GetMouseMode();
	
	UPROPERTY(BlueprintAssignable)
	FOnMouseModeChanged OnMouseModeChanged;
	
protected:
	virtual void SetupInputComponent() override;
    	
	virtual void BeginPlay() override;
    
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_StandardPlay;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_Building;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess = "true"))
	UInputDataConfig* InputActions;

	void OnClick();

	void ZoomCamera(const FInputActionValue& Value);

	void MoveCameraOnXYPlane(const FInputActionValue& Value);
	
	void BeginDragMoveCamera(const FInputActionValue& Value);
	void DragMoveCamera(const FInputActionValue& Value);
	
	void BeginDragRotatingCamera(const FInputActionValue& Value);
	void DragRotateCamera(const FInputActionValue& Value);

	void RotateCameraAroundYawAxis(const FInputActionValue& Value);

	void RotateBuilding(const FInputActionValue& Value);
	
	void ExitBuildMode(const FInputActionValue& Value);
	
	void ApplyMappingContext(const UInputMappingContext* MappingContext, int32 Priority);
	void RemoveMappingContext(const UInputMappingContext* MappingContext);
	
	UFUNCTION()
	void HandleMappingContextFromMouseMode(UMouseMode* MouseMode);
};
