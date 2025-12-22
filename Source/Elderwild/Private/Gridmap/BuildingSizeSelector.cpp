#include "Gridmap/UI/BuildingSizeSelector.h"

#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

#include "Gridmap/UI/BuildingSizeButton.h"
#include "Logging/GridLog.h"

void UBuildingSizeSelector::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!SizeWrapBox) return;
	
	SizeWrapBox->ClearChildren();
	
	TArray<FIntVector2> BuildingSizes = {
		{1,1}, {1,2}, {1,3},
		{2,1}, {2,2}, {2,3},
		{3,1}, {3,2}, {3,3}
	};
	
	for (const FIntVector2& Size : BuildingSizes)
	{
		UBuildingSizeButton* Button = NewObject<UBuildingSizeButton>(this);
		UTextBlock* Text = NewObject<UTextBlock>(this);
		
		if (Text && Button)
		{
			Button->Init(Size);
			Text->SetText(
				FText::FromString(
					FString::Printf(TEXT("%i x %i"), Size.X, Size.Y)	
				)	
			);
			
			Button->AddChild(Text);
			
			Button->OnSizeSelected.AddUObject(this, &UBuildingSizeSelector::HandleSizeButtonClicked);
			
			ButtonToSize.Add(Button, Size);
			
			SizeWrapBox->AddChild(Button);
		}
	}
}

void UBuildingSizeSelector::HandleSizeButtonClicked(FIntVector2 BuildingSize)
{
	UE_LOG(GridLog, Display, TEXT("Broadcasting new building size {%i, %i} to selection tile"), BuildingSize.X, BuildingSize.Y);
	OnBuildingSizeSelected.Broadcast(BuildingSize);
}
