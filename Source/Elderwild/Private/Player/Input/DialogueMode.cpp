#include "Player/Input/DialogueMode.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridVisuals.h"

void UDialogueMode::Init(APlayerController* InController, AGrid* InGrid)
{
	Super::Init(InController, InGrid);

	if (Grid) Grid->UnhoverTile();
}

void UDialogueMode::Click()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked in dialogue mode"));
}

void UDialogueMode::BeginDestroy()
{
	Super::BeginDestroy();

	if (Grid && Grid->GetGridVisuals())
	{
		Grid->GetGridVisuals()->SelectionOpacity = 0.25f;
	}
}
