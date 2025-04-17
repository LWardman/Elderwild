#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class UOccupancyMap;
class UProceduralMeshComponent;
class UGridFactory;

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
	// TODO : repeated uproperty variables that can be mismatched, make component?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	int32 NumRows = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	int32 NumCols = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants")
	int32 TileSize = 10;

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
	
	int32 GetGridWidth() const {return NumCols * TileSize;}

	int32 GetGridHeight() const {return NumRows * TileSize;}

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

private:
	UPROPERTY(EditAnywhere, Category = "Buildings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Building;
	
	UPROPERTY()
	UOccupancyMap* OccupancyMap = nullptr;

	UPROPERTY(EditAnywhere, Category = "Grid")
	UGridFactory* GridFactory;
};
