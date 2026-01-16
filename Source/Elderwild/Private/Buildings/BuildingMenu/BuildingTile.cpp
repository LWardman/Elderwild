#include "Buildings/BuildingMenu/BuildingTile.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Buildings/BuildingData.h"
#include "Logging/BuildingLog.h"

void UBuildingTile::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	const UBuildingData* Data = Cast<UBuildingData>(ListItemObject);
	
	if (!Data)
	{
		UE_LOG(BuildingLog, Warning, TEXT("Gave null BuildingData to BuildingTile"));
		return;
	}
	
	if (Name) Name->SetText(Data->DisplayName);
	if (Cost) Cost->SetText(FText::AsNumber(Data->Cost));
	if (Icon) Icon->SetBrushFromTexture(Data->Icon, true);
}
