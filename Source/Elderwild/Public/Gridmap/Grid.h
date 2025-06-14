#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class UOccupancyMap;
class UProceduralMeshComponent;
class UGridFactory;
class UGridDimensions;
class UGridVisuals;
class USelectionTile;

struct FGridRenderData;
struct FLine;

// TODO : write tests

// TODO : factor selection out into its own class
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
	UGridDimensions* GetGridDimensions() const {return GridDimensions;}

	UGridVisuals* GetGridVisuals() const {return GridVisuals;}

	UOccupancyMap* GetOccupancyMap() const {return OccupancyMap;}
	
	void HoverTile(FVector Location);

	void UnhoverTile();

	void TryBuild(FIntVector2 TileToBuildOn);

	// TODO : this is a middle man function, remove it
	void SetSelectionMaterialColour(FLinearColor NewColor);

private:
	void SetSelectedTile(FIntVector2 Coord);

	void SetSelectionMaterialBasedOnBuildValidity(FIntVector2 Coord);
	
	UPROPERTY()
	UMaterialInstanceDynamic* LineMaterial;

	UPROPERTY()
	UProceduralMeshComponent* LinesProceduralMesh;

	UPROPERTY(EditAnywhere, Category = "Construction", meta=(AllowPrivateAccess))
	USelectionTile* SelectionTile;

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
