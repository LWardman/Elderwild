#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "House.generated.h"

class UInhabitanceComponent;
class UEntranceLocationComponent;

UCLASS()
class ELDERWILD_API AHouse : public ABuilding
{
	GENERATED_BODY()

public:	
	AHouse();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="Building Components", meta=(AllowPrivateAccess))
	UInhabitanceComponent* InhabitanceComponent;
	
	UPROPERTY(EditAnywhere, Category="Building Components", meta=(AllowPrivateAccess))
	UEntranceLocationComponent* EntranceLocationComponent;
};
