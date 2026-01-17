#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EntranceLocationComponent.generated.h"

class ABuilding;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDERWILD_API UEntranceLocationComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	void Init(FIntVector2 BuildingSize);
	
private:	
	void SetEntranceLocation(FIntVector2 BuildingSize);
	void SpawnDebugSphereAtEntrance() const;
};
