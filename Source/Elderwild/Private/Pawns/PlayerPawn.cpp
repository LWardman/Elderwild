#include "Pawns/PlayerPawn.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Actors/Grid.h"
#include "Camera/CameraComponent.h"
#include "GameModes/DevGameMode.h"


APlayerPawn::APlayerPawn()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
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

	HandlePlayerCursor();
}

// TODO : move this to controller class
void APlayerPawn::HandlePlayerCursor()
{
	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	checkf(GameMode, TEXT("Handling player cursor could not be done because the game mode is invalid"));

	AGrid* Grid = GameMode->GetGrid();
	checkf(Grid, TEXT("Handling player cursor could not be done because the grid cannot be found"));

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	checkf(PlayerController, TEXT("Handling player cursor could not be done because the controller is invalid"));
	
	FHitResult Hit;

	if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit))
	{
	    HoverTile(Grid, Hit.Location);   
    }
	else
	{
		UnhoverTile(Grid);
	}
}

void APlayerPawn::HoverTile(AGrid* Grid, FVector Location)
{
	checkf(Grid, TEXT("Passed a nullptr in place of the grid"));

	int32 GridRow;
	int32 GridCol;
	Grid->LocationToTile(Location, GridRow, GridCol);

	Grid->SetSelectedTile(GridRow, GridCol);
}

void APlayerPawn::UnhoverTile(AGrid* Grid)
{
	checkf(Grid, TEXT("Passed a nullptr in place of the grid"));

	// Passing invalid row & tile forces no selection
	Grid->SetSelectedTile(-1, -1);
}
