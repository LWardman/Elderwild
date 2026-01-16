#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "BuildingTile.generated.h"

class UImage;
class UTextBlock;

// This is the tile representing a building in a UTileView
UCLASS()
class ELDERWILD_API UBuildingTile
	: public UUserWidget
	, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Cost;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
