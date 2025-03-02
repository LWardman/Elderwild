#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;

/** A camera which is controlled by the player.
*/
UCLASS()
class ELDERWILD_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Most of the input will be handled by the controller, not here.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera will be the root component.
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

private:
	/** Checks if player is hovering the grid with their mouse,
	 * if they are, delegate that to the grid.
	*/
	void DelegateCursorToGrid() const;
};
