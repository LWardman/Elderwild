#include "Buildings/BuildingMenu/BuildingButton.h"

UBuildingButton::UBuildingButton()
{
    OnClicked.AddDynamic(this, &UBuildingButton::BroadcastBuildingMenuButtonPressed);
}

void UBuildingButton::BroadcastBuildingMenuButtonPressed()
{
    if (BuildingData)
    {
        OnBuildingMenuButtonPressed.Broadcast(BuildingData);
    }    
}