#include "Buildings/Buildingmenu/BuildingTabWidget.h"

#include "Components/Button.h"

void UBuildingTabWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (TabButton) TabButton->OnClicked.AddDynamic(this, &UBuildingTabWidget::HandleClicked);
}

void UBuildingTabWidget::HandleClicked()
{
	OnTabButtonClicked.Broadcast(BuildTab);
}
