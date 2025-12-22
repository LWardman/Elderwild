#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSizeSelector.generated.h"

class UButton;
class UWrapBox;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuildingSizeSelected, FIntVector2);

UCLASS()
class ELDERWILD_API UBuildingSizeSelector : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnBuildingSizeSelected OnBuildingSizeSelected;
	
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UWrapBox* SizeWrapBox;
	
private:
	UPROPERTY()
	TMap<UButton*, FIntVector2> ButtonToSize;
	
	UFUNCTION()
	void HandleSizeButtonClicked(FIntVector2 BuildingSize);
};
