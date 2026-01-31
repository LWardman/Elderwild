#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingTabWidget.generated.h"

class UButton;
enum class EBuildTab : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTabButtonClicked, EBuildTab, BuildTab);

UCLASS()
class ELDERWILD_API UBuildingTabWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="BuildTab")
	EBuildTab BuildTab;
	
	UPROPERTY(BlueprintAssignable, Category="BuildTab")
	FOnTabButtonClicked OnTabButtonClicked;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* TabButton;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void HandleClicked();
};
