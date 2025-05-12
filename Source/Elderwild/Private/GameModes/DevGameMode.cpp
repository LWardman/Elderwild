#include "GameModes/DevGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"
#include "Calendar/Calendar.h"
#include "Player/PlayerPawn.h"
#include "Player/ControlledCamera.h"

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

// TODO : is this the right place to be doing this?
FCameraBoundaries ADevGameMode::CalculateCameraBoundariesFromGrid()
{
	if (GetGrid() == nullptr || GetGrid()->GetGridDimensions() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grid or its dimensions is a nullptr"));
	}

	FVector GridMinimum = GetGrid()->GetActorLocation();
	FVector GridMaximum = GridMinimum;
	GridMaximum.X += GetGrid()->GetGridDimensions()->GetGridWidth();
	GridMaximum.Y += GetGrid()->GetGridDimensions()->GetGridHeight();

	FVector GridPadding = FVector(500, 500, 0);
	
	FCameraBoundaries CameraBoundaries;
	CameraBoundaries.Min = GridMinimum - GridPadding;
	CameraBoundaries.Max = GridMaximum + GridPadding;

	return CameraBoundaries;
}
