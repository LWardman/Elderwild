#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICreatureController.generated.h"

class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class ELDERWILD_API AAICreatureController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAICreatureController();
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorTreeManager;

protected:
	
	virtual void OnPossess(APawn* InPawn) override;	
};
