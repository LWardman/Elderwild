#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class UOccupancyMap;
class UProceduralMeshComponent;
class UGridFactory;
class UGridDimensions;

struct FGridRenderData;
struct FLine;

// TODO : write tests?
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	FLinearColor LineColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	float LineOpacity = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	FLinearColor SelectionColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	float SelectionOpacity = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Constants")
	UMaterialInterface* Material;

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
	
	UPROPERTY(EditAnywhere, Category = "Grid")
    	UGridDimensions* GridDimensions;

private:
	UPROPERTY(EditAnywhere, Category = "Buildings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Building;
	
	UPROPERTY()
	UOccupancyMap* OccupancyMap = nullptr;

	UPROPERTY(EditAnywhere, Category = "Grid")
	UGridFactory* GridFactory;
};
