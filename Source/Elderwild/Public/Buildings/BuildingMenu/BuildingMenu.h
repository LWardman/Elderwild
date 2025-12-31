#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingMenu.generated.h"

class UTileView;
class UBuildingData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingSelected, const UBuildingData*, BuildingData);

UCLASS()
class ELDERWILD_API UBuildingMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

    UPROPERTY()
    FBuildingSelected OnBuildingSelected;

private:
    // TODO : What is the best class for this? Is it allowed to have a UTileView of UButtons?
    UPROPERTY(meta = (BindWidget))
    UTileView* Buildings;

    void CreateBuildingButtons();

    UFUNCTION()
    void BroadcastBuildingSelected(UBuildingData* BuildingData);
};
