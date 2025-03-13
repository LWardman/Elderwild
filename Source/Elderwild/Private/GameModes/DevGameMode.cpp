#include "GameModes/DevGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Controllers/ElderwildController.h"
#include "Actors/Grid.h"
#include "Pawns/PlayerPawn.h"

ADevGameMode::ADevGameMode()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AElderwildController::StaticClass();
}

void ADevGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	Grid = FindGrid(); // Can still be a nullptr, use with care.
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

AGrid* ADevGameMode::GetGrid() const 
{
	if (Grid == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grid is a nullptr"));
	}
	
	return Grid;
}
