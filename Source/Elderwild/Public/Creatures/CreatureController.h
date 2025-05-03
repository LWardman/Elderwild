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

protected:
	
	virtual void OnPossess(APawn* InPawn) override;	
};
