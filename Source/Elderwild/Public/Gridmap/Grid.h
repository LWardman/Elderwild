#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class UOccupancyMap;
class UProceduralMeshComponent;

struct FGridRenderData
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
};

struct FLine
{
	FVector Start;
	FVector End;
};


// TODO : Class is doing too much. Refactor Grid to have multiple components. GridFactory, OccupancyMap, BuildingComponent etc..
UCLASS()
class ELDERWILD_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrid();

protected:
	virtual void BeginPlay() override;

public:

	virtual void OnConstruction(const FTransform &Transform) override;

	void CreateParallelHorizontalLines(FGridRenderData& GridRenderData);

	void CreateParallelVerticalLines(FGridRenderData& GridRenderData);

	void CreateMeshSectionFromVerticesAndTriangles(UProceduralMeshComponent* Mesh, FGridRenderData& GridRenderData);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	int32 NumCols = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	int32 TileSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	int32 LineThickness = 10;

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
	void CreateLine(const FLine& Line, const float Thickness, FGridRenderData& GridRenderData);

	int32 GetGridWidth() const;

	int32 GetGridHeight() const;

	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, float Opacity);

public:
	FIntVector2 LocationToTile(FVector Location);

	FVector2D CornerOfTileToGridLocation(FIntVector2 Coord);

	FVector2D CenterOfTileToGridLocation(FIntVector2 Coord);

	void SetSelectedTile(FIntVector2 Coord);

	bool TileIsValid(FIntVector2 Coord);

	void HoverTile(FVector Location);

	void UnhoverTile();

	void TryBuild(FIntVector2 TileToBuildOn);

	UPROPERTY(EditAnywhere, Category = "Buildings")
	TSubclassOf<AActor> Building;

private:
	UPROPERTY()
	UOccupancyMap* OccupancyMap = nullptr;
};
