#include "Controllers/ElderwildController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

#include "Pawns/PlayerPawn.h"

AElderwildController::AElderwildController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true; 
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AElderwildController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<APlayerPawn>(GetPawn());
	checkf(PlayerPawn, TEXT("Controller could not find the player pawn"));

	Movement = PlayerPawn->Movement;
	checkf(Movement, TEXT("Controller could not find the pawns floating movement component"));
}

void AElderwildController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	InterpolateCameraFieldOfView(DeltaSeconds);
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
		EnhancedInputComponent->BindAction(IA_DragMoveCamera, ETriggerEvent::Triggered, this, &AElderwildController::DragMoveCamera);

		EnhancedInputComponent->BindAction(IA_DragRotateCamera, ETriggerEvent::Triggered, this, &AElderwildController::DragRotateCamera);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AElderwildController::OnClickStarted()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked!"));
}

void AElderwildController::MoveCameraOnXYPlane(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	checkf(PlayerPawn, TEXT("Can't rotate without a pawn"));
	FVector ForwardVector = PlayerPawn->GetActorForwardVector();

	// Quick way to project the forward vector onto the XY plane
	ForwardVector.Z = 0.0f;			
	ForwardVector.Normalize();
	
	FVector RightVector = PlayerPawn->GetActorRightVector();
	
	FVector MovementDirection = ForwardVector * MovementVector.X + RightVector * MovementVector.Y;

	checkf(Movement, TEXT("Cannot move without a movement component"));
	Movement->AddInputVector(MovementDirection);
}

void AElderwildController::RotateCameraAroundYawAxis(const FInputActionValue& Value)
{
	const float Direction = Value.GetMagnitude();

	checkf(PlayerPawn, TEXT("Can't rotate without a pawn"));
	FRotator CurrentRotation = PlayerPawn->GetActorRotation();

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	FRotator DeltaRotator = FRotator{0.0f, DeltaTime * RotationSpeed * Direction, 0.0f};

	FRotator NewRotation = CurrentRotation + DeltaRotator;
	
	PlayerPawn->SetActorRotation(NewRotation);
}

void AElderwildController::ZoomCamera(const FInputActionValue& Value)
{
	// Increment target FOV by 2 in axis direction
	TargetFieldOfView -= Value.Get<float>() * 2;
	TargetFieldOfView = FMath::Clamp(TargetFieldOfView, MinimumFieldOfView, MaximumFieldOfView);
}

void AElderwildController::DragMoveCamera(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Drag Move Camera!"));
}

void AElderwildController::DragRotateCamera(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Drag Rotate Camera!"));
}

void AElderwildController::InterpolateCameraFieldOfView(float DeltaSeconds)
{
	float DifferenceBetweenTargetAndActualFieldOfView = TargetFieldOfView - FieldOfView;
	float InterpSpeed = FMath::Abs(DifferenceBetweenTargetAndActualFieldOfView);

	FieldOfView = FMath::FInterpTo(FieldOfView, TargetFieldOfView, DeltaSeconds, InterpSpeed);

	checkf(PlayerPawn, TEXT("Can't zoom without a pawn"));
	checkf(PlayerPawn->Camera, TEXT("PlayerPawn Camera not found"));
	PlayerPawn->Camera->SetFieldOfView(FieldOfView);
}
