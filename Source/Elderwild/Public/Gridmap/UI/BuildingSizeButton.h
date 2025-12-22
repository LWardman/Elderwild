#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "BuildingSizeButton.generated.h"

class UTextBlock;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSizeSelected, FIntVector2);

UCLASS()
class ELDERWILD_API UBuildingSizeButton : public UButton
{
	GENERATED_BODY()
	
public:
	void Init(const FIntVector2& InSize);
	
	FOnSizeSelected OnSizeSelected;
	
protected:
	UFUNCTION()
	void OnBuildingButtonPressed();

	FIntVector2 BuildingSize = {1, 1};
};
