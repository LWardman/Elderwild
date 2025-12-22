#include "Gridmap/UI/BuildingSizeButton.h"

#include "Logging/GridLog.h"

void UBuildingSizeButton::Init(const FIntVector2& InSize)
{
	BuildingSize = InSize;
	OnClicked.AddDynamic(this, &UBuildingSizeButton::OnBuildingButtonPressed);
}

void UBuildingSizeButton::OnBuildingButtonPressed()
{
	UE_LOG(GridLog, Display, TEXT("Broadcasting new building size {%i, %i} to selector"), BuildingSize.X, BuildingSize.Y);
	OnSizeSelected.Broadcast(BuildingSize);
}
