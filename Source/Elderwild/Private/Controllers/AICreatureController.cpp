#include "Controllers/AICreatureController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AAICreatureController::AAICreatureController()
{
	BehaviorTreeManager = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	checkf(BehaviorTreeManager, TEXT("BehaviorTreeManager could not be created"));

	bStartAILogicOnPossess = true;
}

void AAICreatureController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	
	if (BehaviorTree && UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent))
	{
		BehaviorTreeManager->StartTree(*BehaviorTree);
	}
}
