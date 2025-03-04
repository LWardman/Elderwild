#include "Pawns/PlayerPawn.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameMode.h"

#include "Actors/Grid.h"
#include "Camera/CameraComponent.h"
#include "GameModes/DevGameMode.h"


APlayerPawn::APlayerPawn()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera...
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
	Camera->SetRelativeRotation(FRotator(-60, 0, 0));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandlePlayerCursor();
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::HandlePlayerCursor()
{
	APlayerController* Controller = Cast<APlayerController>(GetController());
	checkf(Controller, TEXT("Handling player cursor could not be done because the controller is invalid"));

	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	checkf(GameMode, TEXT("Handling player cursor could not be done because the game mode is invalid"));

	AGrid* Grid = GameMode->GetGrid();
	checkf(Grid, TEXT("Handling player cursor could not be done because the grid cannot be found"));

	FHitResult Hit;

	if (Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit))
	{
	    HoverTile(Grid);   
    }
	else
	{
		UnhoverTile();
	}
}

void APlayerPawn::HoverTile(AGrid* Grid)
{
	checkf(Grid, TEXT("Passed a nullptr in place of the grid"));

	int32 GridRow;
	int32 GridCol;
	bool IsValid;
	Grid->LocationToTile(Hit.Location, GridRow, GridCol, IsValid);

	Grid->SetSelectedTile(GridRow, GridCol);
}

void APlayerPawn::UnhoverTile(AGrid* Grid)
{
	checkf(Grid, TEXT("Passed a nullptr in place of the grid"));

	// Passing invalid row & tile forces no selection
	Grid->SetSelectedTile(-1, -1);
}
