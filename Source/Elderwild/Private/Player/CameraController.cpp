#include "Player/CameraController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Player/PlayerPawn.h"
#include "Player/ControlledCamera.h"
#include "Player/Input/InputDataConfig.h"
#include "Player/Input/CursorInteractor.h"
#include "Buildings/BuildingDirection.h"
#include "Logging/ControlsLog.h"
#include "Player/Input/BuildMode.h"

ACameraController::ACameraController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true; 
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;

	CursorInteractor = CreateDefaultSubobject<UCursorInteractor>(TEXT("Cursor Interactor"));
	CameraComponent = CreateDefaultSubobject<UControlledCamera>(TEXT("Camera"));
}

void ACameraController::ChangeMouseMode(EMouseModeType ModeType)
{
	if (CursorInteractor) CursorInteractor->ChangeMouseMode(ModeType);
}

const UMouseMode* ACameraController::GetMouseMode()
{
	if (!CursorInteractor) return nullptr;
	return CursorInteractor->GetMouseMode();
}

void ACameraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	ApplyMappingContext(IMC_StandardPlay, 0);

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

		// RotatingBuilding
		EnhancedInputComponent->BindAction(InputActions->RotateBuilding, ETriggerEvent::Completed, this, &ACameraController::RotateBuilding);
		
		// Exit build mode
		EnhancedInputComponent->BindAction(InputActions->ExitBuildMode, ETriggerEvent::Completed, this, &ACameraController::ExitBuildMode);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACameraController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetPawn()))
	{
		Movement = PlayerPawn->Movement;
		CameraComponent = PlayerPawn->Camera;
	}

	OnMouseModeChanged.AddDynamic(this, &ACameraController::HandleMappingContextFromMouseMode);
	ChangeMouseMode(EMouseModeType::Inspect);
}

void ACameraController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorInteractor) CursorInteractor->UpdateHover();
}

void ACameraController::OnClick()
{
	if (CursorInteractor) CursorInteractor->HandleClick();
}

void ACameraController::ZoomCamera(const FInputActionValue& Value)
{
	if (CameraComponent) CameraComponent->ZoomCamera(Value.GetMagnitude());
}

void ACameraController::MoveCameraOnXYPlane(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	if (CameraComponent && Movement)
	{
		FVector MovementDirection = CameraComponent->CalculateCameraMovementVectorOnXYPlane(Input);
		Movement->AddInputVector(MovementDirection);
	}
}

void ACameraController::BeginDragMoveCamera(const FInputActionValue& Value)
{
	FVector2d Cursor = FVector2D::ZeroVector;
	if (GetMousePosition(Cursor.X, Cursor.Y) && CameraComponent)
	{
		CameraComponent->BeginDragMovement(Cursor);
	}
}

void ACameraController::DragMoveCamera(const FInputActionValue& Value)
{
	FVector2D Cursor = FVector2D::Zero();
	if (GetMousePosition(Cursor.X, Cursor.Y) && CameraComponent)
	{
		CameraComponent->DragMove(Cursor);
	}
}

void ACameraController::BeginDragRotatingCamera(const FInputActionValue& Value)
{
	FVector2D Cursor = FVector2D::ZeroVector;
	if (GetMousePosition(Cursor.X, Cursor.Y) && CameraComponent)
	{
		CameraComponent->BeginDragRotate(Cursor);
	}
}

void ACameraController::DragRotateCamera(const FInputActionValue& Value)
{
	FVector2D Cursor = FVector2D::Zero();
	if (GetMousePosition(Cursor.X, Cursor.Y) && CameraComponent)
	{
		CameraComponent->DragRotate(Cursor);
	}
}

void ACameraController::RotateCameraAroundYawAxis(const FInputActionValue& Value)
{
	if (CameraComponent) CameraComponent->RotateAroundYawAxis(Value.GetMagnitude());
}

void ACameraController::RotateBuilding(const FInputActionValue& Value)
{
	UBuildingDirection::RotateClockwise();
}

void ACameraController::ExitBuildMode(const FInputActionValue& Value)
{
	ChangeMouseMode(EMouseModeType::Inspect);
}

void ACameraController::ApplyMappingContext(const UInputMappingContext* MappingContext, int32 Priority)
{
	if (!MappingContext)
	{
		UE_LOG(ControlsLog, Error, TEXT("Attempted to apply a null mapping context. Aborting.."));
		return;
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		UE_LOG(ControlsLog, Display, TEXT("Adding a mapping context"));
		Subsystem->AddMappingContext(MappingContext, Priority);
	}
}

void ACameraController::RemoveMappingContext(const UInputMappingContext* MappingContext)
{
	if (!MappingContext)
	{
		UE_LOG(ControlsLog, Error, TEXT("Attempted to remove a null mapping context. Aborting.."));
		return;
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		UE_LOG(ControlsLog, Display, TEXT("Removing a mapping context"));
		Subsystem->RemoveMappingContext(MappingContext);
	}
}

void ACameraController::HandleMappingContextFromMouseMode(UMouseMode* MouseMode)
{
	if (!MouseMode) return;
	
	if (MouseMode->IsA(UBuildMode::StaticClass()))
	{
		ApplyMappingContext(IMC_Building, 1);
	}
	else
	{
		RemoveMappingContext(IMC_Building);
	}
}
