#include "Gridmap/GridDimensions.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGridDimensions, "Elderwild.Gridmap.Dimensions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

namespace
{
	void InitializesWell(UGridDimensions* GridDimensions, FAutomationTestBase* Test)
	{
		Test->TestGreaterEqual(TEXT("Rows is non-negative"), GridDimensions->GetNumRows(), 0);
		Test->TestGreaterEqual(TEXT("Cols is non-negative"), GridDimensions->GetNumCols(), 0);
	
		Test->TestGreaterEqual(TEXT("TileSize greater than 0"), GridDimensions->GetTileSize(), 1);
		Test->TestGreaterEqual(TEXT("LineThickness is non-negative"), GridDimensions->GetLineThickness(), 0);
	}

	void IdentifiesCoordValidity(UGridDimensions* GridDimensions, FAutomationTestBase* Test)
	{
		GridDimensions->Init(10, 10, 200, 10);

		FIntVector2 ErrorCoord = FIntVector2(-1, -1);
		Test->TestEqual(TEXT("Error coord is invalid"), GridDimensions->TileIsValid(ErrorCoord), false);
		
		FIntVector2 OverflowsWidth = FIntVector2(10, 0);
		Test->TestEqual(TEXT("Width overflow coord is invalid"), GridDimensions->TileIsValid(OverflowsWidth), false);

		FIntVector2 OverflowsHeight = FIntVector2(0, 10);
		Test->TestEqual(TEXT("Height overflow coord is invalid"), GridDimensions->TileIsValid(OverflowsHeight), false);

		FIntVector2 OverflowsBoth = FIntVector2(10, 10);
		Test->TestEqual(TEXT("Overflow coord is invalid"), GridDimensions->TileIsValid(OverflowsBoth), false);

		FIntVector2 ExcessivelyBigCoord = FIntVector2(100000000, 100000000);
		Test->TestEqual(TEXT("Excessively large coord is invalid"), GridDimensions->TileIsValid(ExcessivelyBigCoord), false);

		FIntVector2 OriginCoord = FIntVector2(0, 0);
		Test->TestEqual(TEXT("Origin coord is valid"), GridDimensions->TileIsValid(OriginCoord), true);

		FIntVector2 MaxWidth = FIntVector2(9, 0);
		Test->TestEqual(TEXT("MaxWidth coord is valid"), GridDimensions->TileIsValid(MaxWidth), true);

		FIntVector2 MaxHeight = FIntVector2(0, 9);
		Test->TestEqual(TEXT("MaxHeight coord is valid"), GridDimensions->TileIsValid(MaxHeight), true);

		FIntVector2 Extremity = FIntVector2(9, 9);
		Test->TestEqual(TEXT("Extremity coord is valid"), GridDimensions->TileIsValid(Extremity), true);

		GridDimensions->Init(200, 100, 200, 10);

		FIntVector2 WonkyGridExtremity = FIntVector2(199, 99);
		Test->TestEqual(TEXT("WonkyGridExtremity coord is valid"), GridDimensions->TileIsValid(WonkyGridExtremity), true);
	}
}

bool FGridDimensions::RunTest(const FString& Parameters)
{
	UGridDimensions* GridDimensions = NewObject<UGridDimensions>();
	TestNotNull(TEXT("Null check passes"), GridDimensions);

	// Testing Initialization with different failing params
	GridDimensions->Init(-1, -1, -100, -20);
	InitializesWell(GridDimensions, this);

	GridDimensions->Init(1, 1, 200, 10);
	InitializesWell(GridDimensions, this);

	GridDimensions->Init(-100, 100, 0, 500);
	InitializesWell(GridDimensions, this);

	GridDimensions->Init(10, 10, 200, 10);
	InitializesWell(GridDimensions, this);

	IdentifiesCoordValidity(GridDimensions, this);

	// TODO : how to test these properly?
	
	//FVector2D CenterOfTileToGridLocation(FIntVector2 Coord);
	//FVector2D CornerOfTileToGridLocation(FIntVector2 Coord);
	//FIntVector2 LocationToTile(FVector HitLocation) const;
	
	return true;
}