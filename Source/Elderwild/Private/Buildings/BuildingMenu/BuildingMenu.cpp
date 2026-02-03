#include "Buildings/BuildingMenu/BuildingMenu.h"

#include "Components/TileView.h"
#include "Kismet/GameplayStatics.h"

#include "Buildings/BuildingData.h"
#include "Buildings/Buildingmenu/BuildingTabWidget.h"
#include "Logging/BuildingLog.h"
#include "Player/CameraController.h"
#include "Buildings/BuildingMenu/BuildMenuTabData.h"

void UBuildingMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SwitchTab(EBuildTab::Buildings);
	
	if (BuildingsTab)
	{
		BuildingsTab->OnTabButtonClicked.AddDynamic(this, &UBuildingMenu::SwitchTab);
	}
	if (RoadsTab)
	{
		RoadsTab->OnTabButtonClicked.AddDynamic(this, &UBuildingMenu::SwitchTab);
	}
	if (DecorationsTab)
	{
		DecorationsTab->OnTabButtonClicked.AddDynamic(this, &UBuildingMenu::SwitchTab);
	}
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
		BuildingSelected.Broadcast(Data);
		CameraController->ChangeMouseMode(EMouseModeType::Build);
	}
}

void UBuildingMenu::SetTileViewFromBuildingTabEntries(TObjectPtr<UBuildMenuTabData> BuildingTabEntries)
{
	if (!Buildings || !BuildingTabEntries) return;
	
	Buildings->ClearListItems();
	
	for (TObjectPtr<UBuildingData> BuildingData : BuildingTabEntries->BuildingTabData)
	{
		if (BuildingData) Buildings->AddItem(BuildingData);
	}
	
	Buildings->OnItemClicked().AddUObject(this, &UBuildingMenu::OnBuildingSelected);
}

void UBuildingMenu::SwitchTab(EBuildTab NewTab)
{
	SetTileViewFromBuildingTabEntries(TabToBuildingMap.FindChecked(NewTab));
}
