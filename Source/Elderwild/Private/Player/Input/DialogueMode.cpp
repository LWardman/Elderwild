#include "Player/Input/DialogueMode.h"

#include "Dialogue/DialogueComponent.h"
#include "Gridmap/Grid.h"
#include "Gridmap/GridVisuals.h"
#include "Player/PlayerPawn.h"

void UDialogueMode::Init(APlayerController* InController, AGrid* InGrid)
{
	Super::Init(InController, InGrid);

	if (Grid) Grid->UnhoverTile();
}

void UDialogueMode::Click()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked in dialogue mode"));
	
	if (!Controller) return;
	if (APlayerPawn* Player = Cast<APlayerPawn>(Controller->GetPawn()))
	{
		if (UDialogueComponent* Dialogue = Player->DialogueComponent)
        {
        	Dialogue->MoveToNextMessage();
        }
	}
}

void UDialogueMode::BeginDestroy()
{
	Super::BeginDestroy();

	if (Grid && Grid->GetGridVisuals())
	{
		Grid->GetGridVisuals()->SelectionOpacity = 0.25f;
	}
}
