#include "Creatures/CreatureController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"


ACreatureController::ACreatureController()
{
	BehaviorTreeManager = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	checkf(BehaviorTreeManager, TEXT("BehaviorTreeManager could not be created"));

	bStartAILogicOnPossess = true;
}

void ACreatureController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	
	if (BehaviorTree && UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent))
	{
		BehaviorTreeManager->StartTree(*BehaviorTree);
	}
}
