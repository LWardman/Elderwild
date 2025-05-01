#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

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

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	int32 MaxNumberOfInhabitants = 3;
};
