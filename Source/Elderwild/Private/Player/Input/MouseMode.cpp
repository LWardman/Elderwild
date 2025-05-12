#include "Player/Input/MouseMode.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"

void UMouseMode::Init(APlayerController* InController, AGrid* InGrid)
{
	Controller = InController;
	Grid = InGrid;

	UE_LOG(LogTemp, Display, TEXT("Entering MouseMode : %s"), *GetClass()->GetName());
}

void UMouseMode::Click()
{
	//UE_LOG(LogTemp, Display, TEXT("Clicked"));
	checkf(Controller && Grid && Grid->GetGridDimensions(), TEXT("Nullptr in mouse mode Click()"));
}

void UMouseMode::Hover()
{
	//UE_LOG(LogTemp, Display, TEXT("Hovered"));
	checkf(Controller && Grid, TEXT("Nullptr in build mode Hover()"));
}

void UMouseMode::BeginDestroy()
{
	Super::BeginDestroy();
	
	UE_LOG(LogTemp, Display, TEXT("Exiting MouseMode : %s"), *GetClass()->GetName());
}

