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
    UPROPERTY()
    FBuildingSelected BuildingSelected;

protected:
    UPROPERTY(meta = (BindWidget))
    UTileView* Buildings;

    UPROPERTY(EditAnywhere)
    TArray<TObjectPtr<UBuildingData>> AvailableBuildings;
    
    virtual void NativeOnInitialized() override;
    
    UFUNCTION()
    void OnBuildingSelected(UObject* SelectedItem);
};
