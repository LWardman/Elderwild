#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Calendar/SeasonCycler.h"
#include "SeasonPanel.generated.h"

class UImage;
class UGridPanel;
enum class ESeason : uint8;

/**
 * The UI display of the current season. Highlights the active season whilst greying out the others.
 */
UCLASS()
class ELDERWILD_API USeasonPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void UpdateSeason(const ESeason NewSeason);

protected:
	UPROPERTY(meta=(BindWidget))
	UGridPanel* GridPanel;
	
	UPROPERTY(meta=(BindWidget))
	UImage* SpringImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* SummerImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* AutumnImage;
	
	UPROPERTY(meta=(BindWidget))
	UImage* WinterImage;
	
	void ActivateImage(UImage* SeasonImage);
	void DeactivateImage(UImage* SeasonImage);
	
	UPROPERTY()
	TMap<ESeason, UImage*> SeasonToImage;
	
	const FLinearColor GreyTint = FLinearColor(0.1f, 0.1f, 0.1f, 1.0f);
	const FLinearColor NoTint = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
};
