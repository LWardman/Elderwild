#include "GameModes/DevGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Controllers/ElderwildController.h"
#include "Actors/Grid.h"

ADevGameMode::ADevGameMode()
{
	PlayerControllerClass = AElderwildController::StaticClass();

	// set default pawn class to our blueprinted pawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Elderwild/Pawns/BP_PlayerPawn.BP_PlayerPawn"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Elderwild/Controllers/BP_ElderwildController.BP_ElderwildController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ADevGameMode::BeginPlay()
{
	Super::BeginPlay();

	Grid = FindGrid();
}

AGrid* ADevGameMode::FindGrid()
{
	TArray<AActor*> GridActors;
	UGameplayStatics::GetAllActorsOfClass(this, AGrid::StaticClass(), GridActors);

	if (GridActors.IsValidIndex(0))
	{
		return Cast<AGrid>(GridActors[0]);
	}
	
	UE_LOG(LogTemp, Error, TEXT("Cannot find grid, returning nullptr"));
	return nullptr;
}

AGrid* ADevGameMode::GetGrid()
{
	if (Grid == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grid is a nullptr"));
	}
	
	return Grid;
}
