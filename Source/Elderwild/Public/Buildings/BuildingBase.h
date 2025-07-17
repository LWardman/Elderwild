#pragma once

#include "CoreMinimal.h"
#include "BuildingDirection.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

class ACreatureBase;
enum class ECompassDirection : uint8;

UCLASS()
class ELDERWILD_API ABuildingBase : public AActor
{
	GENERATED_BODY()

public:	
	ABuildingBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	int32 GetNumberOfInhabitants() const;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	int32 MaxNumberOfCreatures = 3;

	UPROPERTY()
	TArray<ACreatureBase*> InhabitingCreatures;

	ECompassDirection BuildingDirection = ECompassDirection::South;

	FVector EntranceLocation;

	FIntVector2 GetBuildingSize() const {return BuildingSize;}

protected:
	void SetBuildingSize(FIntVector2 NewBuildingSize);

private:
	void FindEntranceLocation();

	void SpawnDebugSphereAtEntrance() const;

	UPROPERTY(EditAnywhere, Category = "Defaults", meta=(AllowPrivateAccess))
	FIntVector2 BuildingSize = FIntVector2(1, 1);
};
