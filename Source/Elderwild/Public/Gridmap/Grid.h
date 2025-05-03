#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class UOccupancyMap;
class UProceduralMeshComponent;
class UGridFactory;
class UGridDimensions;
class UGridVisuals;

struct FGridRenderData;
struct FLine;

// TODO : write tests?
// TODO : factor out colour selector into its own class
UCLASS()
class ELDERWILD_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrid();

	virtual void OnConstruction(const FTransform &Transform) override;
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	UGridVisuals* GridVisuals;

	UPROPERTY()
	UMaterialInstanceDynamic* LineMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterial;

	UPROPERTY()
	UProceduralMeshComponent* LinesProceduralMesh;

	UPROPERTY()
	UProceduralMeshComponent* SelectionProceduralMesh;

private:
	void CreateMeshSectionFromRenderData(UProceduralMeshComponent* Mesh, FGridRenderData& GridRenderData);

	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, float Opacity);

public:
	void SetSelectedTile(FIntVector2 Coord);

	void HoverTile(FVector Location);

	void UnhoverTile();

	void TryBuild(FIntVector2 TileToBuildOn);

	void SetSelectionMaterialColour(FLinearColor NewColor);

	void SetSelectionMaterialBasedOnBuildValidity(FIntVector2 Coord);
	
	UPROPERTY(EditAnywhere, Category = "Grid")
	UGridDimensions* GridDimensions;

	bool IsInBuildMode = false;

private:
	UPROPERTY(EditAnywhere, Category = "Buildings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Building;
	
	UPROPERTY()
	UOccupancyMap* OccupancyMap = nullptr;

	UPROPERTY(EditAnywhere, Category = "Grid")
	UGridFactory* GridFactory;
};
