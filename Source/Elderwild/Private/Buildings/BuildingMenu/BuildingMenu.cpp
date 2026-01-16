#include "Buildings/BuildingMenu/BuildingMenu.h"

#include "Components/TileView.h"
#include "Kismet/GameplayStatics.h"

#include "Buildings/BuildingData.h"
#include "Logging/BuildingLog.h"
#include "Player/CameraController.h"

void UBuildingMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (!Buildings) return;
	
	Buildings->ClearListItems();
	
	for (UBuildingData* Data : AvailableBuildings)
	{
		if (Data) Buildings->AddItem(Data);
	}
	
	Buildings->OnItemClicked().AddUObject(this, &UBuildingMenu::OnBuildingSelected);
}

void UBuildingMenu::OnBuildingSelected(UObject* SelectedItem)
{
	const UBuildingData* Data = Cast<UBuildingData>(SelectedItem);
	if (!Data)
	{
		UE_LOG(BuildingLog, Warning, TEXT("Selected a tile with a null data asset"));
		return;
	}
	
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (ACameraController* CameraController = Cast<ACameraController>(Controller))
	{
		// This order is bad for going from build mode into build mode, since exiting build mode overwrites
		BuildingSelected.Broadcast(Data);
		CameraController->ChangeMouseMode(EMouseModeType::Build);
	}
}
