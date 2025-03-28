#include "Controllers/ElderwildController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

#include "Actors/Grid.h"
#include "GameModes/DevGameMode.h"
#include "Pawns/PlayerPawn.h"
#include "Components/ElderwildsCamera.h"


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
		EnhancedInputComponent->BindAction(IA_Click, ETriggerEvent::Started, this, &AElderwildController::OnClickStarted);

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

	PlayerPawn = Cast<APlayerPawn>(GetPawn());
	checkf(PlayerPawn, TEXT("Controller could not find the player pawn"));

	Movement = PlayerPawn->Movement;
	checkf(Movement, TEXT("Controller could not find the pawns floating movement component"));

	CameraComponent = PlayerPawn->Camera;
	checkf(CameraComponent, TEXT("Controller could not find the pawns camera component"));
}

void AElderwildController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleCursor();
}

void AElderwildController::OnClickStarted()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked!"));
}

void AElderwildController::HandleCursor()
{
	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	checkf(GameMode, TEXT("Handling player cursor could not be done because the game mode is invalid"));

	AGrid* Grid = GameMode->GetGrid();
	checkf(Grid, TEXT("Handling player cursor could not be done because the grid cannot be found"));

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
	float CursorPositionX = 0.0f;
	float CursorPositionY = 0.0f;
	if (GetMousePosition(CursorPositionX, CursorPositionY))
	{
		CurrentMousePositionMove = FVector{CursorPositionX, CursorPositionY, 0.0f};

		checkf(PlayerPawn, TEXT("Can't move a nullptr pawn"));
		FVector CurrentLocation = PlayerPawn->GetActorLocation();
		
		FVector MouseDeltaPosition = CurrentMousePositionMove - BeginningMousePositionMove;
		
		BeginningMousePositionMove = CurrentMousePositionMove;

		// TODO : DRY
		FVector ForwardVectorXY = CameraComponent->GetForwardXYVector();
		FVector ForwardMovement = ForwardVectorXY * MouseDeltaPosition.Y * DragCameraMoveSensitivity;

		FVector RightVector = PlayerPawn->GetActorRightVector();
		FVector SidewaysMovement = - RightVector * MouseDeltaPosition.X * DragCameraMoveSensitivity;

		FVector NewLocation = CurrentLocation + ForwardMovement + SidewaysMovement;
		
		PlayerPawn->SetActorLocation(NewLocation);
	}
}

void AElderwildController::BeginDragRotatingCamera(const FInputActionValue& Value)
{
	UpdateVariablesWithCursorPosition(BeginningMousePositionRotate, CurrentMousePositionRotate);
}

void AElderwildController::DragRotateCamera(const FInputActionValue& Value)
{
	float CursorPositionX = 0.0f;
	float CursorPositionY = 0.0f;
	if (GetMousePosition(CursorPositionX, CursorPositionY))
	{
		CurrentMousePositionRotate = FVector{CursorPositionX, CursorPositionY, 0.0f};
		
		const FVector MouseDeltaPosition = BeginningMousePositionRotate - CurrentMousePositionRotate;
		
		BeginningMousePositionRotate = CurrentMousePositionRotate;

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
	float CursorPositionX = 0.0f;
   float CursorPositionY = 0.0f;
   if (GetMousePosition(CursorPositionX, CursorPositionY))
   {
   	CurrentPosition = FVector{CursorPositionX, CursorPositionY, 0.0f};
   	BeginningPosition = CurrentPosition;
   }
}
