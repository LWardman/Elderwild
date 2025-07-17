#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionTile.generated.h"

class UProceduralMeshComponent;
class AGrid;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ELDERWILD_API USelectionTile : public UActorComponent
{
	GENERATED_BODY()

public:
	USelectionTile();
	void Init(AGrid* InGrid);

	void SetSelectionMaterialColour(FLinearColor NewColor);

	void UpdateSelectedTile(bool IsValidTile, FVector TilePosition);

	TArray<FIntVector2> CalculateRelevantTileLocations(FIntVector2 BaseTile, FIntVector2 BuildingSize);

private:

	void SetVisibleSections(FIntVector2 BuildingSize);

	bool BuildingSizeIsValid(FIntVector2 BuildingSize);

	TArray<int32> GetRelevantMeshSections(FIntVector2 BuildingSize);

	void RotateRelativeTileAroundBaseBy90(FIntVector2& Tile);

	void LogRelevantTiles(TArray<FIntVector2> Tiles);

	// TODO : add a Building Size variable.
	FIntVector2 MaxBuildingSize = {3, 3};
	
	UPROPERTY()
	UProceduralMeshComponent* ProcMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterial;

	UPROPERTY()
	AGrid* Grid;
};
