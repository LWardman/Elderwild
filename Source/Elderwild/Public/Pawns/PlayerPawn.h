#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class AGrid;

UCLASS()
class ELDERWILD_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	// TODO : find a better name for this function
	void HandlePlayerCursor();

	void HoverTile(AGrid* Grid, FVector Location);

	void UnhoverTile(AGrid* Grid);
};
