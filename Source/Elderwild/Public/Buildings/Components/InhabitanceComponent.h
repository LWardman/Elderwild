#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InhabitanceComponent.generated.h"

class AHouse;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDERWILD_API UInhabitanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInhabitanceComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	int32 GetNumberOfInhabitants() const { return InhabitingCreatures.Num(); };
	int32 GetMaxInhabitants() const { return MaxNumberOfCreatures; }
	bool HasSpace() const { return GetNumberOfInhabitants() < GetMaxInhabitants(); }
	bool IsFull() const { return !HasSpace(); }
	
	TArray<AActor*> GetInhabitants() const { return InhabitingCreatures; }
	bool RegisterInhabitant(AActor* NewInhabitant);
	
	void RegisterPotentialInhabitants();

	bool ShouldAutomaticallyPopulate() const { return bAutomaticallyPopulate; }

protected:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	bool bAutomaticallyPopulate = false;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	int32 MaxNumberOfCreatures = 3;

	UPROPERTY()
	TArray<AActor*> InhabitingCreatures;
	
	UPROPERTY()
	AHouse* Parent;
};
