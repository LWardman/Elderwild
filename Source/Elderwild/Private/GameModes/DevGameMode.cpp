#include "GameModes/DevGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Controllers/ElderwildController.h"
#include "Actors/Grid.h"

ADevGameMode::ADevGameMode()
{
	// TODO : remove below comment when testing proves everything is okay
	//PlayerControllerClass = AElderwildController::StaticClass();

	SetDefaultPawnClass();

	SetDefaultControllerClass();
}

// TODO : violates DRY with SetDefaultControllerClass?
void ADevGameMode::SetDefaultPawnClass()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Elderwild/Pawns/BP_PlayerPawn.BP_PlayerPawn"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADevGameMode::SetDefaultControllerClass()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Elderwild/Controllers/BP_ElderwildController.BP_ElderwildController"));
	if(PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
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
