#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionTile.generated.h"

class UBuildingSizeSelector;
class UProceduralMeshComponent;
class AGrid;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ELDERWILD_API USelectionTile : public UActorComponent
{
	GENERATED_BODY()

public:
	USelectionTile();
	void Init(AGrid* InGrid);
	virtual void BeginPlay() override;

	void SetSelectionMaterialColour(FLinearColor NewColor);

	void UpdateSelectedTile(bool IsValidTile, FVector TilePosition);
	
	void SetBuildingSize(const FIntVector2 NewBuildingSize) { BuildingSize = NewBuildingSize; }

	TArray<FIntVector2> CalculateRelevantTileLocations(FIntVector2 BaseTile);

private:

	void SetVisibleSections();

	bool BuildingSizeIsValid();

	TArray<int32> GetRelevantMeshSections();

	void RotateRelativeTileAroundBaseBy90(FIntVector2& Tile);

	void LogRelevantTiles(TArray<FIntVector2> Tiles);
	
	FIntVector2 BuildingSize = {1, 1};
	FIntVector2 MaxBuildingSize = {3, 3};
	
	UPROPERTY()
	UProceduralMeshComponent* ProcMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterial;

	UPROPERTY()
	AGrid* Grid;
	
	UPROPERTY()
	UBuildingSizeSelector* BuildingSizeSelectorWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UBuildingSizeSelector> BuildingSizeSelectorClass;
	
	void CreateBuildingSizeSelectorWidget();
	
	UFUNCTION()
	void OnBuildingSizeWidgetButtonClicked(FIntVector2 BroadcastedBuildingSize);
};
