#include "GameModes/DevGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Actors/Grid.h"
#include "Calendar/Calendar.h"
#include "Pawns/PlayerPawn.h"

ADevGameMode::ADevGameMode()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	SetDefaultPlayerController();

	Calendar = CreateDefaultSubobject<UCalendar>(TEXT("Calendar"));
}

void ADevGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	Grid = FindGrid(); // Can still be a nullptr, use with care.
}

void ADevGameMode::SetDefaultPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint>
		ControllerBlueprint(TEXT("Blueprint'/Game/Elderwild/Controllers/BP_ElderwildController.BP_ElderwildController'"));

	if (ControllerBlueprint.Object)
	{
		PlayerControllerClass = ControllerBlueprint.Object->GeneratedClass;
	}
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
