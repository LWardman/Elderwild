#include "Calendar/UI/SeasonPanel.h"

#include "Components/GridPanel.h"
#include "Components/Image.h"

void USeasonPanel::NativeConstruct()
{
	if (GridPanel)
	{
		GridPanel->SetColumnFill(0, 1);
		GridPanel->SetColumnFill(1, 1);
		GridPanel->SetColumnFill(2, 1);
		GridPanel->SetColumnFill(3, 1);
		
		GridPanel->SetRowFill(0, 1);
	}
	
	SeasonToImage.Add(ESeason::Spring, SpringImage);
	SeasonToImage.Add(ESeason::Summer, SummerImage);
	SeasonToImage.Add(ESeason::Autumn, AutumnImage);
	SeasonToImage.Add(ESeason::Winter, WinterImage);
}

void USeasonPanel::UpdateSeason(const ESeason NewSeason)
{
	TArray<ESeason> PossibleSeasons = {ESeason::Spring, ESeason::Summer, ESeason::Autumn, ESeason::Winter};
	
	for (const ESeason Season : PossibleSeasons)
	{
		if (Season == NewSeason)
		{
			ActivateImage(SeasonToImage.FindChecked(Season));
		}
		else
		{
			DeactivateImage(SeasonToImage.FindChecked(Season));
		}
	}
}

void USeasonPanel::ActivateImage(UImage* SeasonImage)
{
	if (SeasonImage) SeasonImage->SetColorAndOpacity(NoTint);
}

void USeasonPanel::DeactivateImage(UImage* SeasonImage)
{
	if (SeasonImage) SeasonImage->SetColorAndOpacity(GreyTint);
}
