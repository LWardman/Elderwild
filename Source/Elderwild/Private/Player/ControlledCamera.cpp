#include "Player/ControlledCamera.h"

#include "Kismet/GameplayStatics.h"

#include "GameModes/DevGameMode.h"
#include "Components/CameraZoom.h"
#include "Components/CameraRotationComponent.h"
#include "Components/CameraTranslationComponent.h"

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
