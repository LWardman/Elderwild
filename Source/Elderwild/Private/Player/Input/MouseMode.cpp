#include "Player/Input/MouseMode.h"

#include "Gridmap/Grid.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/DevGameMode.h"
#include "Player/CameraController.h"

void UMouseMode::OnMouseModeEnter()
{
	UE_LOG(LogTemp, Display, TEXT("Entering %s"), *GetClass()->GetName());
	
	if (ACameraController* Controller = Cast<ACameraController>(GetController()))
	{
		Controller->OnMouseModeChanged.Broadcast(this);
	}
}

void UMouseMode::Click()
{
	//UE_LOG(LogTemp, Display, TEXT("Clicked"));
}

void UMouseMode::Hover()
{
	//UE_LOG(LogTemp, Display, TEXT("Hovered"));
}

void UMouseMode::OnMouseModeExit()
{
	UE_LOG(LogTemp, Display, TEXT("Exiting MouseMode : %s"), *GetClass()->GetName());
}

APlayerController* UMouseMode::GetController() const
{
	return UGameplayStatics::GetPlayerController(this, 0);
}

AGrid* UMouseMode::GetGrid() const
{
	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this));
	
	if (!GameMode) return nullptr;
	
	return GameMode->GetGrid();
}

FHitResult UMouseMode::GetHitResultUnderCursor() const
{
	FHitResult Hit;
	if (APlayerController* Controller = GetController())
	{
		Controller->GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	}
	return Hit;
}
