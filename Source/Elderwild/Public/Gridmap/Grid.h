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

// TODO : write tests
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
	UGridDimensions* GetGridDimensions() {return GridDimensions;}

	UGridVisuals* GetGridVisuals() {return GridVisuals;}

	UOccupancyMap* GetOccupancyMap() {return OccupancyMap;}
	
	void HoverTile(FVector Location);

	void UnhoverTile();

	void TryBuild(FIntVector2 TileToBuildOn);

	void SetSelectionMaterialColour(FLinearColor NewColor);

private:
	void SetSelectionMaterialFromMouseMode();

	// TODO : Move to factory?
	void CreateMeshSectionFromRenderData(UProceduralMeshComponent* Mesh, FGridRenderData& GridRenderData);

	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, float Opacity);

	void SetSelectedTile(FIntVector2 Coord);

	void SetSelectionMaterialBasedOnBuildValidity(FIntVector2 Coord);
	
	UPROPERTY()
	UMaterialInstanceDynamic* LineMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterial;

	UPROPERTY()
	UProceduralMeshComponent* LinesProceduralMesh;

	UPROPERTY()
	UProceduralMeshComponent* SelectionProceduralMesh;

	UPROPERTY(EditAnywhere, Category = "Construction", meta=(AllowPrivateAccess))
	UGridDimensions* GridDimensions;
	
	UPROPERTY(EditAnywhere, Category = "Buildings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Building;
	
	UPROPERTY()
	UOccupancyMap* OccupancyMap = nullptr;

	UPROPERTY(EditAnywhere, Category = "Construction")
	UGridFactory* GridFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta=(AllowPrivateAccess))
	UGridVisuals* GridVisuals;
};
