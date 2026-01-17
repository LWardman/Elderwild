#pragma once

#include "CoreMinimal.h"
#include "BuildingDirection.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class ELDERWILD_API ABuilding : public AActor
{
	GENERATED_BODY()

public:	
	ABuilding();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	ECompassDirection BuildingDirection = ECompassDirection::South;

	FIntVector2 GetBuildingSize() const {return BuildingSize;}

private:
	UPROPERTY(EditAnywhere, Category="Building", meta=(AllowPrivateAccess))
	FIntVector2 BuildingSize = FIntVector2(1, 1);
	
	UPROPERTY(EditAnywhere, Category="Building", meta=(AllowPrivateAccess))
	UStaticMeshComponent* Mesh;
};
