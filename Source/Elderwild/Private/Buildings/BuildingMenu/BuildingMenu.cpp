#include "Buildings/BuildingMenu/BuildingMenu.h"

#include "Buildings/BuildingData.h"

bool UBuildingMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	CreateBuildingButtons();	

	return true;
}

void UBuildingMenu::CreateBuildingButtons()
{
	if (!Buildings) return;

	// Bind the buttons building data here
	// Buildings->Entry.OnBuildingMenuButtonPressed.AddDynamic(this, &BroadcastBuildingSelected);
}

void UBuildingMenu::BroadcastBuildingSelected(UBuildingData* BuildingData)
{
	if (!BuildingData) return;

	OnBuildingSelected.Broadcast(BuildingData);
}