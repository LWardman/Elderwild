#include "Player/Input/DialogueMode.h"

#include "Dialogue/DialogueComponent.h"
#include "Gridmap/Grid.h"
#include "Gridmap/GridVisuals.h"
#include "Player/PlayerPawn.h"

void UDialogueMode::OnMouseModeEnter()
{
	if (AGrid* Grid = GetGrid())
	{
		Grid->UnhoverTile();
	}
	
	APlayerController* Controller = GetController();
	if (!Controller) return;
	
	if (APlayerPawn* Player = Cast<APlayerPawn>(Controller->GetPawn()))
	{
		if (UDialogueComponent* Dialogue = Player->DialogueComponent)
		{
			UE_LOG(LogTemp, Display, TEXT("Entering dialogue"));
			Dialogue->EnterDialogue();
		}
	}	
}

void UDialogueMode::Click()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked in dialogue mode"));
	
	APlayerController* Controller = GetController();
	if (!Controller) return;
	if (APlayerPawn* Player = Cast<APlayerPawn>(Controller->GetPawn()))
	{
		if (UDialogueComponent* Dialogue = Player->DialogueComponent)
        {
        	Dialogue->MoveToNextMessage();
        }
	}
}

void UDialogueMode::OnMouseModeExit()
{
	Super::OnMouseModeExit();
	
	AGrid* Grid = GetGrid();
	if (Grid && Grid->GetGridVisuals())
	{
		Grid->GetGridVisuals()->SelectionOpacity = 0.25f;
	}
}
