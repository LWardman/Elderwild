#include "Creatures/CreatureController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ACreatureController::ACreatureController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BehaviorTreeManager = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	checkf(BehaviorTreeManager, TEXT("BehaviorTreeManager could not be created"));

	bStartAILogicOnPossess = true;
}

void ACreatureController::UpdateSleepState(bool bInSleepState)
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsBool(BB_ShouldBeSleeping, bInSleepState);
	}
}

void ACreatureController::UpdateHome(AActor* InHome)
{
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		BB->SetValueAsObject(BB_Home, InHome);
	}
}

void ACreatureController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Display, TEXT("Starting Behavior Tree for %s"), *InPawn->GetName());
	StartAI();
}

void ACreatureController::StartAI()
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	
	if (BehaviorTree && BehaviorTreeManager && UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent))
	{
		BehaviorTreeManager->StartTree(*BehaviorTree);
	}	
}
