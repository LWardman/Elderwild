#include "Player/PlayerPawn.h"

#include "GameFramework/FloatingPawnMovement.h"

#include "Player/ControlledCamera.h"
#include "Dialogue/DialogueComponent.h"
#include "Inventory/InventoryComponent.h"


APlayerPawn::APlayerPawn()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Camera = CreateDefaultSubobject<UControlledCamera>(TEXT("Camera"));
	RootComponent = Camera;
	Camera->SetRelativeRotation(FRotator(-60, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("Dialogue Component"));
	checkf(DialogueComponent, TEXT("Dialogue component initialized poorly"));

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Camera)
	{
		FCameraBoundaries Boundaries = Camera->GetCameraBoundaries();

		FVector CurrentLocation = GetActorLocation();
		FVector ClampedLocation = CurrentLocation;

		ClampedLocation.X = FMath::Clamp(ClampedLocation.X, Boundaries.Min.X, Boundaries.Max.X);
		ClampedLocation.Y = FMath::Clamp(ClampedLocation.Y, Boundaries.Min.Y, Boundaries.Max.Y);

		SetActorLocation(ClampedLocation);
	}
}
