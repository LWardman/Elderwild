#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingAssignmentComponent.generated.h"

class ABuilding;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingChanged, ABuilding*, NewBuilding);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDERWILD_API UBuildingAssignmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FBuildingChanged BuildingChanged;
	
	void AssignToBuilding(ABuilding* NewBuilding);

	void RemoveFromBuilding();

	bool IsAssigned() const;
	
	FVector GetBuildingLocation() const;
	
private:
	UPROPERTY(VisibleAnywhere)
	ABuilding* Building;
};
