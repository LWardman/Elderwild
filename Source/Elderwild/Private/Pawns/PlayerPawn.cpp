#include "Pawns/PlayerPawn.h"

#include "Actors/Grid.h"
#include "Camera/CameraComponent.h"
#include "GameModes/DevGameMode.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera, set as root and rotation...
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
	Camera->SetRelativeRotation(FRotator(-60, 0, 0)); // Pointing downwards at a slant
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DelegateCursorToGrid();
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::DelegateCursorToGrid() const
{
	// Player controller provides access to the player's cursor.
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC == nullptr)	
	{
		UE_LOG(LogTemp, Error, TEXT("Could not get player controller, check if its initialised."));
		return;
	}

	// Game mode is providing access to the grid.
	ADevGameMode* GM = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Either GameMode does not exist, or it can't be cast to the Dev mode"));
		return;
	}

	// Ensure the grid is found and valid.
	AGrid* Grid = GM->GetGrid();
	if (Grid == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get grid from game mode"));
		return;
	}
	
	FHitResult Hit;
	if (PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit)) // If successful hit
	{
		int32 GridRow;
		int32 GridCol;
		bool IsValid;
		Grid->LocationToTile(Hit.Location, GridRow, GridCol, IsValid);
		Grid->SetSelectedTile(GridRow, GridCol);
	}
	else // If hit isn't successful
	{
		// Passing invalid row & tile to force no selection
		Grid->SetSelectedTile(-1, -1);
	}
}