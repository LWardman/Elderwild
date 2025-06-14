#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GridVisuals.generated.h"


UCLASS()
class ELDERWILD_API UGridVisuals : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	FLinearColor LineColor = FLinearColor::Black;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	FLinearColor BuildValidColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	FLinearColor BuildInvalidColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	FLinearColor InspectColor = FLinearColor::Gray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	float LineOpacity = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	float SelectionOpacity = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Constants")
	UMaterialInterface* Material;

	static UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, float Opacity, AGrid* Grid)
	{
		checkf(Grid, TEXT("Passed in a null grid to create a dynamic material instance."));
		checkf(Grid->GetGridVisuals(), TEXT("No grid visuals is assigned to the grid.")); // TODO : this feels wrong
		checkf(Grid->GetGridVisuals()->Material, TEXT("Cannot create dynamic material instance, because no parent material is set"));
	
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Grid->GetGridVisuals()->Material, Grid);
		DynMaterial->SetVectorParameterValue("Color", Color);
		DynMaterial->SetScalarParameterValue("Opacity", Opacity);
	
		return DynMaterial;
	}
};
