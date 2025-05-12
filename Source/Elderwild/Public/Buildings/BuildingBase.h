#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

class ACreatureBase;

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

	int32 GetNumberOfInhabitants();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	int32 MaxNumberOfCreatures = 3;

	UPROPERTY()
	TArray<ACreatureBase*> InhabitingCreatures;
};
