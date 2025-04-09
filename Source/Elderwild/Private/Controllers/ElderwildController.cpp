#include "Controllers/ElderwildController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

#include "Gridmap/Grid.h"
#include "GameModes/DevGameMode.h"
#include "Player/PlayerPawn.h"
#include "Player/ControlledCamera.h"


AElderwildController::AElderwildController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true; 
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AElderwildController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_StandardPlay, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup LMB click
		EnhancedInputComponent->BindAction(IA_Click, ETriggerEvent::Completed, this, &AElderwildController::OnClickStarted);

		// Setup keyboard camera movement
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AElderwildController::MoveCameraOnXYPlane);
		EnhancedInputComponent->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &AElderwildController::RotateCameraAroundYawAxis);
		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &AElderwildController::ZoomCamera);

		// Setup mouse camera movement
		EnhancedInputComponent->BindAction(IA_DragMoveCamera, ETriggerEvent::Started, this, &AElderwildController::BeginDragMoveCamera);
		EnhancedInputComponent->BindAction(IA_DragMoveCamera, ETriggerEvent::Triggered, this, &AElderwildController::DragMoveCamera);

		EnhancedInputComponent->BindAction(IA_DragRotateCamera, ETriggerEvent::Started, this, &AElderwildController::BeginDragRotatingCamera);
		EnhancedInputComponent->BindAction(IA_DragRotateCamera, ETriggerEvent::Triggered, this, &AElderwildController::DragRotateCamera);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AElderwildController::BeginPlay()
{
	Super::BeginPlay();

	SetAndCheckPointers();
}

void AElderwildController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleCursor();
}

void AElderwildController::SetAndCheckPointers()
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
}

void AElderwildController::OnClickStarted()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked!"));

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		FIntVector2 GridTile = Grid->LocationToTile(Hit.Location);

		UE_LOG(LogTemp, Log, TEXT("Tile Hit : %s"), *GridTile.ToString());
	}
}

void AElderwildController::HandleCursor()
{
	FHitResult Hit;
	if (GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		Grid->HoverTile(Hit.Location);
	}
	else
	{
		Grid->UnhoverTile();
	}
}

void AElderwildController::ZoomCamera(const FInputActionValue& Value)
{
	CameraComponent->ZoomCamera(Value.GetMagnitude());
}

void AElderwildController::MoveCameraOnXYPlane(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	FVector MovementDirection = CameraComponent->CalculateCameraMovementVectorOnXYPlane(Input);
	Movement->AddInputVector(MovementDirection);
}

void AElderwildController::BeginDragMoveCamera(const FInputActionValue& Value)
{
	UpdateVariablesWithCursorPosition(BeginningMousePositionMove, CurrentMousePositionMove);
}

void AElderwildController::DragMoveCamera(const FInputActionValue& Value)
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

void AElderwildController::BeginDragRotatingCamera(const FInputActionValue& Value)
{
	UpdateVariablesWithCursorPosition(BeginningMousePositionRotate, CurrentMousePositionRotate);
}

void AElderwildController::DragRotateCamera(const FInputActionValue& Value)
{
	FVector2D Cursor = FVector2d::Zero();
	if (GetMousePosition(Cursor.X, Cursor.Y))
	{
		FVector MouseDeltaPosition = UpdateMousePositionsAndGetDelta(BeginningMousePositionRotate, CurrentMousePositionRotate, Cursor);
		const float RotationMagnitude = DragCameraRotateSensitivity * MouseDeltaPosition.X;
		CameraComponent->RotateAroundYawAxis(RotationMagnitude);
	}
}

void AElderwildController::RotateCameraAroundYawAxis(const FInputActionValue& Value)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const float RotationMagnitude = DeltaTime * RotationSpeed * Value.GetMagnitude();
	CameraComponent->RotateAroundYawAxis(RotationMagnitude);
}

void AElderwildController::UpdateVariablesWithCursorPosition(FVector& BeginningPosition, FVector& CurrentPosition)
{
	FVector2d Cursor = FVector2D::ZeroVector;
   	if (GetMousePosition(Cursor.X, Cursor.Y))
   	{
   		CurrentPosition = FVector{Cursor.X, Cursor.Y, 0.0f};
   		BeginningPosition = CurrentPosition;
   	}
}

FVector AElderwildController::UpdateMousePositionsAndGetDelta(FVector& BeginningPosition, FVector& CurrentPosition, const FVector2d Cursor)
{
	CurrentPosition = FVector{Cursor.X, Cursor.Y, 0.0f};
	const FVector MouseDeltaPosition = BeginningPosition - CurrentPosition;
	BeginningPosition = CurrentPosition;

	return MouseDeltaPosition;
}
