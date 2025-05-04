#include "Gridmap/OccupancyMap.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FOccupancyMap, "Elderwild.Gridmap.OccupancyMap", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

namespace
{
	void InvalidTilesThrowCorrectResponseToGet(UOccupancyMap* OccupancyMap, FAutomationTestBase* Test)
	{
		FIntVector2 ErrorCoord = FIntVector2(-1, -1);
		Test->TestEqual(TEXT("Giving an invalid tile throws an error"), OccupancyMap->GetTileOccupancyState(ErrorCoord), EOccupancyState::NOT_A_TILE);

		FIntVector2 OverflowGridWidth = FIntVector2(1000000, 0);
		Test->TestEqual(TEXT("Giving an overflown width throws an error"), OccupancyMap->GetTileOccupancyState(OverflowGridWidth), EOccupancyState::NOT_A_TILE);

		FIntVector2 OverflowGridHeight = FIntVector2(0, 1000000);
		Test->TestEqual(TEXT("Giving an overflown height throws an error"), OccupancyMap->GetTileOccupancyState(OverflowGridHeight), EOccupancyState::NOT_A_TILE);

		FIntVector2 BigCoord = FIntVector2(10000000, 10000000);
		Test->TestEqual(TEXT("Giving an Excessively large int throws an error"), OccupancyMap->GetTileOccupancyState(BigCoord), EOccupancyState::NOT_A_TILE);
	}

	void InvalidTilesDoNotRespondToSetting(UOccupancyMap* OccupancyMap, FAutomationTestBase* Test)
	{
		FIntVector2 ErrorCoord = FIntVector2(-1, -1);
		Test->TestEqual(TEXT("Giving an invalid tile throws an error"), OccupancyMap->GetTileOccupancyState(ErrorCoord), EOccupancyState::NOT_A_TILE);
		OccupancyMap->SetTileOccupancyState(ErrorCoord, EOccupancyState::EMPTY);
		Test->TestEqual(TEXT("Giving an invalid tile throws an error"), OccupancyMap->GetTileOccupancyState(ErrorCoord), EOccupancyState::NOT_A_TILE);
	}

	void AllValidTilesCanBeChecked(UOccupancyMap* OccupancyMap, FAutomationTestBase* Test, int32 GridWidth, int32 GridHeight)
	{
		OccupancyMap->Init(GridWidth, GridHeight);
		
		for (int32 Row = 0; Row < GridHeight; Row++)
		{
			for (int32 Col = 0; Col < GridWidth; Col++)
			{
				FIntVector2 TileCoord = FIntVector2(Row, Col);
				Test->TestEqual(TEXT("Tile correctly initialized to be empty"), OccupancyMap->GetTileOccupancyState(TileCoord), EOccupancyState::EMPTY);
			}
		}
	}

	void AllValidTilesCanBeSet(UOccupancyMap* OccupancyMap, FAutomationTestBase* Test, int32 GridWidth, int32 GridHeight)
	{
		OccupancyMap->Init(GridWidth, GridHeight);
		
		for (int32 Row = 0; Row < GridHeight; Row++)
		{
			for (int32 Col = 0; Col < GridWidth; Col++)
			{
				FIntVector2 TileCoord = FIntVector2(Row, Col);
				Test->TestEqual(TEXT("Tile correctly initialized to be empty"), OccupancyMap->GetTileOccupancyState(TileCoord), EOccupancyState::EMPTY);
				OccupancyMap->SetTileOccupancyState(TileCoord, EOccupancyState::OCCUPIED);
				Test->TestEqual(TEXT("Tile correctly initialized to be empty"), OccupancyMap->GetTileOccupancyState(TileCoord), EOccupancyState::OCCUPIED);
			}
		}
	}
}

bool FOccupancyMap::RunTest(const FString& Parameters)
{
	UOccupancyMap* OccupancyMap = NewObject<UOccupancyMap>();

	TestNotNull(TEXT("OccupancyMap generated properly"), OccupancyMap);
	
	int32 GridWidth = 10;
	int32 GridHeight = 10;
	OccupancyMap->Init(GridWidth, GridHeight);

	InvalidTilesThrowCorrectResponseToGet(OccupancyMap, this);
	InvalidTilesDoNotRespondToSetting(OccupancyMap, this);

	// Square grid
	AllValidTilesCanBeChecked(OccupancyMap, this, 10, 10);
	AllValidTilesCanBeSet(OccupancyMap, this, 10, 10);

	// Vertical rectangle grid
	AllValidTilesCanBeChecked(OccupancyMap, this, 20, 100);
	AllValidTilesCanBeSet(OccupancyMap, this, 20, 100);

	// Horizontal rectangle grid
	AllValidTilesCanBeChecked(OccupancyMap, this, 200, 100);
	AllValidTilesCanBeSet(OccupancyMap, this, 200, 100);

	// Empty grid
	FIntVector2 ZeroCoord = FIntVector2::ZeroValue;
	OccupancyMap->Init(0, 0);
	TestEqual(TEXT("Giving the zero coord on an empty grid throws an error"), OccupancyMap->GetTileOccupancyState(ZeroCoord), EOccupancyState::NOT_A_TILE);
	OccupancyMap->SetTileOccupancyState(ZeroCoord, EOccupancyState::EMPTY);
	TestEqual(TEXT("Giving the zero coord on an empty grid throws an error"), OccupancyMap->GetTileOccupancyState(ZeroCoord), EOccupancyState::NOT_A_TILE);

	// Negative grid
	FIntVector2 NegativeCoord = FIntVector2(-10, -10);
	OccupancyMap->Init(-10, -10);
	TestEqual(TEXT("Giving the zero coord on a negative grid throws an error"), OccupancyMap->GetTileOccupancyState(ZeroCoord), EOccupancyState::NOT_A_TILE);
	OccupancyMap->SetTileOccupancyState(NegativeCoord, EOccupancyState::EMPTY);
	TestEqual(TEXT("Giving the zero coord on a negative grid throws an error"), OccupancyMap->GetTileOccupancyState(ZeroCoord), EOccupancyState::NOT_A_TILE);

	FIntVector2 ErrorCoord = FIntVector2(-1, -1);
	TestEqual(TEXT("Giving the error coord on a negative grid throws an error"), OccupancyMap->GetTileOccupancyState(ErrorCoord), EOccupancyState::NOT_A_TILE);
	OccupancyMap->SetTileOccupancyState(NegativeCoord, EOccupancyState::EMPTY);
	TestEqual(TEXT("Giving the error coord on a negative grid throws an error"), OccupancyMap->GetTileOccupancyState(ErrorCoord), EOccupancyState::NOT_A_TILE);
	
	return true;
}