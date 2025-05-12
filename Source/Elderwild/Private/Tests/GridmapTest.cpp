#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGridmap, "Elderwild.Gridmap", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FGridmap::RunTest(const FString& Parameters)
{
	AGrid* Grid = NewObject<AGrid>();

	TestNotNull(TEXT("Grid successfully created"), Grid);

	// TODO : this is inconclusive
	
	//UGridDimensions* GetGridDimensions() {return GridDimensions;}
	
	//void HoverTile(FVector Location);

	//void UnhoverTile();

	//void TryBuild(FIntVector2 TileToBuildOn);
	
	//void ReceiveMouseMode(EMouseMode NewMouseMode);
	
	return true;
}