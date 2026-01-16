#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionTile.generated.h"

class UBuildingMenu;
class UProceduralMeshComponent;
class AGrid;
class UBuildingData;

// TODO : replace Grid references here with GetOwner()
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
	
	UFUNCTION()
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
	
	UFUNCTION()
	void OnBuildingDataUpdated(const UBuildingData* InBuildingData);
};
