#include "Player/CameraController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

#include "Gridmap/Grid.h"
#include "GameModes/DevGameMode.h"
#include "Player/PlayerPawn.h"
#include "Player/ControlledCamera.h"
#include "Player/InputDataConfig.h"
#include "Player/CursorInteractor.h"


ACameraController::ACameraController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true; 
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ACameraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_StandardPlay, 0);
	}

	if(!InputActions) return;

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup LMB click
		EnhancedInputComponent->BindAction(InputActions->Click, ETriggerEvent::Completed, this, &ACameraController::OnClick);

		// Setup keyboard camera movement
		EnhancedInputComponent->BindAction(InputActions->Move, ETriggerEvent::Triggered, this, &ACameraController::MoveCameraOnXYPlane);
		EnhancedInputComponent->BindAction(InputActions->Rotate, ETriggerEvent::Triggered, this, &ACameraController::RotateCameraAroundYawAxis);
		EnhancedInputComponent->BindAction(InputActions->Zoom, ETriggerEvent::Triggered, this, &ACameraController::ZoomCamera);

		// Setup mouse camera movement
		EnhancedInputComponent->BindAction(InputActions->DragMoveCamera, ETriggerEvent::Started, this, &ACameraController::BeginDragMoveCamera);
		EnhancedInputComponent->BindAction(InputActions->DragMoveCamera, ETriggerEvent::Triggered, this, &ACameraController::DragMoveCamera);

		EnhancedInputComponent->BindAction(InputActions->DragRotateCamera, ETriggerEvent::Started, this, &ACameraController::BeginDragRotatingCamera);
		EnhancedInputComponent->BindAction(InputActions->DragRotateCamera, ETriggerEvent::Triggered, this, &ACameraController::DragRotateCamera);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACameraController::BeginPlay()
{
	Super::BeginPlay();

	SetAndCheckPointers();
}

void ACameraController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorInteractor)
	{
		CursorInteractor->UpdateHover();
	}
}

void ACameraController::SetAndCheckPointers()
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetPawn());
	checkf(PlayerPawn, TEXT("Controller could not find the player pawn"));

	Movement = PlayerPawn->Movement;
	checkf(Movement, TEXT("Controller could not find the pawns floating movement component"));

	CameraComponent = PlayerPawn->Camera;
	checkf(CameraComponent, TEXT("Controller could not find the pawns camera component"));

	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	checkf(GameMode, TEXT("Controller could not find the game mode"));

	Grid = GameMode->GetGrid();
	checkf(Grid, TEXT("Handling player cursor could not be done because the grid cannot be found"));

	CursorInteractor = NewObject<UCursorInteractor>();
	CursorInteractor->Initialize(this, Grid);
	checkf(CursorInteractor, TEXT("CursorInteractor not initialized properly"));
}

void ACameraController::OnClick()
{
	if (CursorInteractor)
	{
		CursorInteractor->HandleClick();
	}
}

void ACameraController::ZoomCamera(const FInputActionValue& Value)
{
	CameraComponent->ZoomCamera(Value.GetMagnitude());
}

void ACameraController::MoveCameraOnXYPlane(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	FVector MovementDirection = CameraComponent->CalculateCameraMovementVectorOnXYPlane(Input);
	Movement->AddInputVector(MovementDirection);
}

void ACameraController::BeginDragMoveCamera(const FInputActionValue& Value)
{
	UpdateVariablesWithCursorPosition(BeginningMousePositionMove, CurrentMousePositionMove);
}

void ACameraController::DragMoveCamera(const FInputActionValue& Value)
{
	FVector2d Cursor = FVector2d::Zero();
	if (GetMousePosition(Cursor.X, Cursor.Y))
	{
		FVector MouseDeltaPosition = UpdateMousePositionsAndGetDelta(BeginningMousePositionMove, CurrentMousePositionMove, Cursor);
		MouseDeltaPosition *= -1;
		
		FVector ForwardVectorXY = CameraComponent->GetForwardXYVector();
		FVector ForwardMovement = ForwardVectorXY * MouseDeltaPosition.Y * DragCameraMoveSensitivity;

		FVector RightVector = CameraComponent->GetRightVector();
		FVector SidewaysMovement = -1 * RightVector * MouseDeltaPosition.X * DragCameraMoveSensitivity;

		FVector CurrentLocation = CameraComponent->GetComponentLocation();

		FVector NewLocation = CurrentLocation + ForwardMovement + SidewaysMovement;
		
		CameraComponent->SetWorldLocation(NewLocation);
	}
}

void ACameraController::BeginDragRotatingCamera(const FInputActionValue& Value)
{
	UpdateVariablesWithCursorPosition(BeginningMousePositionRotate, CurrentMousePositionRotate);
}

void ACameraController::DragRotateCamera(const FInputActionValue& Value)
{
	FVector2D Cursor = FVector2d::Zero();
	if (GetMousePosition(Cursor.X, Cursor.Y))
	{
		FVector MouseDeltaPosition = UpdateMousePositionsAndGetDelta(BeginningMousePositionRotate, CurrentMousePositionRotate, Cursor);
		const float RotationMagnitude = DragCameraRotateSensitivity * MouseDeltaPosition.X;
		CameraComponent->RotateAroundYawAxis(RotationMagnitude);
	}
}

void ACameraController::RotateCameraAroundYawAxis(const FInputActionValue& Value)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float RotationMagnitude = DeltaTime * RotationSpeed * Value.GetMagnitude();
	CameraComponent->RotateAroundYawAxis(RotationMagnitude);
}

void ACameraController::UpdateVariablesWithCursorPosition(FVector& BeginningPosition, FVector& CurrentPosition)
{
	FVector2d Cursor = FVector2D::ZeroVector;
   	if (GetMousePosition(Cursor.X, Cursor.Y))
   	{
   		CurrentPosition = FVector{Cursor.X, Cursor.Y, 0.0f};
   		BeginningPosition = CurrentPosition;
   	}
}

FVector ACameraController::UpdateMousePositionsAndGetDelta(FVector& BeginningPosition, FVector& CurrentPosition, const FVector2d Cursor)
{
	CurrentPosition = FVector{Cursor.X, Cursor.Y, 0.0f};
	const FVector MouseDeltaPosition = BeginningPosition - CurrentPosition;
	BeginningPosition = CurrentPosition;

	return MouseDeltaPosition;
}
