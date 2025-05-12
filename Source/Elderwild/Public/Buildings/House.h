#pragma once

#include "CoreMinimal.h"
#include "Buildings/BuildingBase.h"
#include "House.generated.h"


UCLASS()
class ELDERWILD_API AHouse : public ABuildingBase
{
	GENERATED_BODY()

public:	
	AHouse();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void TryFillBuildingWithCreatures();

};
