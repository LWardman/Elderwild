#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "BuildingButton.generated.h"

class UBuildingData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingMenuButtonPressed, const UBuildingData*, BuildingData);

UCLASS()
class ELDERWILD_API UBuildingButton : public UButton
{
    GENERATED_BODY()

public:
    UBuildingButton();

    UPROPERTY()
    FBuildingMenuButtonPressed OnBuildingMenuButtonPressed;

private:
    UPROPERTY(EditAnywhere, Category="Building", meta=(AllowPrivateAccess))
    UBuildingData* BuildingData;

    UFUNCTION()
    void BroadcastBuildingMenuButtonPressed();
};
