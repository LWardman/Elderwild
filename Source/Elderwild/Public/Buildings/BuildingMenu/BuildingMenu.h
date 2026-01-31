#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingMenu.generated.h"

class UTileView;
class UBuildingData;
class UBuildMenuTabData;
class UBuildingTabWidget;

UENUM(BlueprintType)
enum class EBuildTab : uint8
{
    Buildings,
    Roads,
    Decorations
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingSelected, const UBuildingData*, BuildingData);

UCLASS()
class ELDERWILD_API UBuildingMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FBuildingSelected BuildingSelected;

protected:
    UPROPERTY(meta=(BindWidget))
    UTileView* Buildings;
    
    // TODO : Turn the collection of building tab widgets into a UPanelWidget
    UPROPERTY(meta=(BindWidget))
    UBuildingTabWidget* BuildingsTab;
    
    UPROPERTY(meta=(BindWidget))
    UBuildingTabWidget* RoadsTab;
    
    UPROPERTY(meta=(BindWidget))
    UBuildingTabWidget* DecorationsTab;
    
    virtual void NativeOnInitialized() override;
    
    UFUNCTION()
    void OnBuildingSelected(UObject* SelectedItem);
    
    void SetTileViewFromBuildingTabEntries(TObjectPtr<UBuildMenuTabData> BuildingTabEntries);
    
    UPROPERTY(EditAnywhere)
    TMap<EBuildTab, TObjectPtr<UBuildMenuTabData>> TabToBuildingMap;
    
    UFUNCTION()
    void SwitchTab(EBuildTab NewTab);
};
