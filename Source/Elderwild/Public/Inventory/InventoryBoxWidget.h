#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "InventoryBoxWidget.generated.h"

class USizeBox;
class UBorder;
class UImage;

UCLASS()
class ELDERWILD_API UInventoryBoxWidget
	: public UUserWidget
	, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UImage* ResourceIcon;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResourceCount;
};
