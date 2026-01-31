#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CreatureController.generated.h"

class UBehaviorTree;
class UBehaviorTreeComponent;

UCLASS()
class ELDERWILD_API ACreatureController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACreatureController();
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorTreeManager;
	
	void UpdateSleepState(bool bInSleepState);
	
	void UpdateHome(AActor* InHome);

protected:
	virtual void OnPossess(APawn* InPawn) override;	
	
private:
	void StartAI();
	
	UPROPERTY(EditDefaultsOnly, Category="Blackboard")
	FName BB_ShouldBeSleeping = "ShouldBeAsleep";
	
	UPROPERTY(EditDefaultsOnly, Category="Blackboard")
	FName BB_Home = "Home";
};
