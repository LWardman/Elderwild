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
class UBuildingData;
class UBuildingMenu;
class ABuilding;

struct FGridRenderData;
struct FLine;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingDataUpdated, const UBuildingData*, BuildingData);

UCLASS()
class ELDERWILD_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AGrid();

	virtual void OnConstruction(const FTransform &Transform) override;
	
	UPROPERTY()
	FBuildingDataUpdated BuildingDataUpdated;
	
protected:
	virtual void BeginPlay() override;

public:
	UGridDimensions* GetGridDimensions() const {return GridDimensions;}
	UGridVisuals* GetGridVisuals() const {return GridVisuals;}
	UOccupancyMap* GetOccupancyMap() const {return OccupancyMap;}
	USelectionTile* GetSelectionTile() const {return SelectionTile;}
	
	void HoverTile(FVector Location);

	void UnhoverTile();

	void TryBuild(FIntVector2 TileToBuildOn);

	// TODO : this is a middle man function, remove it
	void SetSelectionMaterialColour(FLinearColor NewColor);
	
	void SetBuildingData(const UBuildingData* InBuildingData);
	
	void CreateDisplayBuilding();
	void DestroyDisplayBuilding();
	
	void HandleDisplayBuildingMovement(FIntVector2 NewLocation);
	
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
	
	UPROPERTY()
	const UBuildingData* BuildingData;
	
	UPROPERTY()
	ABuilding* DisplayBuilding;
	
	UPROPERTY()
	UOccupancyMap* OccupancyMap = nullptr;

	UPROPERTY(EditAnywhere, Category = "Construction")
	UGridFactory* GridFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals", meta=(AllowPrivateAccess))
	UGridVisuals* GridVisuals;
	
	// TODO : This really isn't the place for this widget to be spawned from
	UPROPERTY()
	UBuildingMenu* BuildingMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UBuildingMenu> BuildingMenuClass;
	
	void CreateBuildingMenuWidget();
	
	UFUNCTION()
	void OnBuildingButtonClicked(const UBuildingData* InBuildingData);
};
