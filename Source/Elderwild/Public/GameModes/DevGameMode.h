#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevGameMode.generated.h"

class AGrid;
class UCalendar;

/** WARNING : ADevGameMode should not be used in the final product,
 *		      it is for testing only. If this game mode wants to be
 *		      used, then make another class with an identical body so
 *		      this can be modified for testing new modes.
 */
UCLASS()
class ELDERWILD_API ADevGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	ADevGameMode();

	virtual void BeginPlay() override;

	void SetDefaultPlayerController();

	// Finds, stores and gets the grid used in play.
	UPROPERTY()
	AGrid* Grid;
	AGrid* FindGrid();
	AGrid* GetGrid() const;

private:
	UPROPERTY()
	UCalendar* Calendar;
};
