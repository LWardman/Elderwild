#include "Pawns/PlayerPawn.h"

#include "GameFramework/FloatingPawnMovement.h"

#include "Components/ControlledCamera.h"


APlayerPawn::APlayerPawn()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Camera = CreateDefaultSubobject<UControlledCamera>(TEXT("Camera"));
	RootComponent = Camera;
	Camera->SetRelativeRotation(FRotator(-60, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
