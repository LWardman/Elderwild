#include "Player/ControlledCamera.h"

#include "Kismet/GameplayStatics.h"

#include "GameModes/DevGameMode.h"
#include "Components/CameraZoomComponent.h"
#include "Components/CameraRotationComponent.h"
#include "Components/CameraTranslationComponent.h"
#include "Logging/ControlsLog.h"

UControlledCamera::UControlledCamera()
{
	PrimaryComponentTick.bCanEverTick = true;

	CameraZoom = CreateDefaultSubobject<UCameraZoomComponent>("CameraZoom");
	CameraRotation = CreateDefaultSubobject<UCameraRotationComponent>("CameraRotation");
	CameraTranslation = CreateDefaultSubobject<UCameraTranslationComponent>("CameraTranslation");
}

void UControlledCamera::BeginPlay()
{
	Super::BeginPlay();

	// TODO : move this?
	SetFieldOfView(FieldOfView);

	if (ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		CameraBoundaries = GameMode->CalculateCameraBoundariesFromGrid();
	}
	
	// TODO : I don't like this design. Surely there's a way to access the parent from the scene component
	if (CameraRotation) CameraRotation->Init(this);
	if (CameraZoom) CameraZoom->Init(this);
	if (CameraTranslation) CameraTranslation->Init(this);
}

void UControlledCamera::ZoomCamera(float Direction)
{
	UE_LOG(ControlsLog, Display, TEXT("Forwarding zoom controls to zoom component"));
	if (CameraZoom) CameraZoom->ZoomCamera(Direction); 
}

FVector UControlledCamera::CalculateCameraMovementVectorOnXYPlane(FVector2D PlayerInput) const
{
	FVector ForwardXY = GetForwardXYVector();
	FVector RightVector = GetRightVector();
	
	return ForwardXY * PlayerInput.X + RightVector * PlayerInput.Y;
}

FVector UControlledCamera::GetForwardXYVector() const 
{
	FVector ForwardVector = GetForwardVector();
	FVector ForwardXY = FVector{ ForwardVector.X, ForwardVector.Y, 0.0f };
	ForwardXY.Normalize();
	
	return ForwardXY;
}
	
void UControlledCamera::BeginDragMovement(FVector2D Cursor)
{
	UE_LOG(ControlsLog, Display, TEXT("Forwarding translation controls to translation component"));
	if (CameraTranslation) CameraTranslation->BeginDragMovement(Cursor); 
}

void UControlledCamera::DragMove(FVector2d Cursor)
{
	//UE_LOG(ControlsLog, Display, TEXT("Forwarding translation controls to translation component"));
	if (CameraTranslation) CameraTranslation->DragMove(Cursor); 
}

void UControlledCamera::BeginDragRotate(FVector2d Cursor)
{
	UE_LOG(ControlsLog, Display, TEXT("Forwarding rotation controls to rotation component"));
	if (CameraRotation) CameraRotation->BeginDragRotate(Cursor); 
}

void UControlledCamera::DragRotate(FVector2d Cursor)
{
	//UE_LOG(ControlsLog, Display, TEXT("Forwarding rotation controls to rotation component"));
	if (CameraRotation) CameraRotation->DragRotate(Cursor); 
}

void UControlledCamera::RotateAroundYawAxis(float RotationDirection)
{
	//UE_LOG(ControlsLog, Display, TEXT("Forwarding rotation controls to rotation component"));
	if (CameraRotation) CameraRotation->RotateAroundYawAxis(RotationDirection);
}
