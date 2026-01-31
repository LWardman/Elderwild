#include "BehaviorTreeTasks/GetRandomGridTile.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#include "GameModes/DevGameMode.h"
#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"

UBTTask_GetRandomGridTile::UBTTask_GetRandomGridTile()
{
	NodeName = "Get Random Grid Tile";
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_GetRandomGridTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;
	
	
	AGameModeBase* GM = UGameplayStatics::GetGameMode(OwnerComp.GetWorld());
	ADevGameMode* GameMode = Cast<ADevGameMode>(GM);
	if (!GameMode) return EBTNodeResult::Failed;
	
	AGrid* Grid = GameMode->GetGrid();
	if (!Grid) return EBTNodeResult::Failed;
	
	UGridDimensions* GridDimensions = Grid->GetGridDimensions();
	if (!GridDimensions) return EBTNodeResult::Failed;
	
	FIntVector2 RandomTile = GridDimensions->GetRandomTile();
	FVector2D TileLocation2D = GridDimensions->CenterOfTileToGridLocation(RandomTile);
	FVector TileLocation = FVector(TileLocation2D.X, TileLocation2D.Y, 0);
	BB->SetValueAsVector("DestinationLocation", TileLocation);
	
	return EBTNodeResult::Succeeded;
}
