#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class UProceduralMeshComponent;

UCLASS()
class ELDERWILD_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY()
	UMaterialInstanceDynamic* LineMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* SelectionMaterial;

private:
	void CreateLine(FVector Start, FVector End, float Thickness, TArray<FVector> Vertices, TArray<int32> Triangles);

	int32 GetGridWidth() const;

	int32 GetGridHeight() const;

	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, float Opacity);

public:
	void LocationToTile(FVector Location, int32& GridRow, int32& GridCol, bool& IsValid);

	void TileToGridLocation(int32 Row, int32 Col, bool ShouldCenter, bool& IsValid, FVector2D& Location);

	void SetSelectedTile(int32 Row, int32 Col);

	bool TileIsValid(int32 Row, int32 Col);
};
