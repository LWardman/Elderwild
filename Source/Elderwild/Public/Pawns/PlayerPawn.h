#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UElderwildsCamera;
class UFloatingPawnMovement;
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
	UElderwildsCamera* Camera;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

	virtual void Tick(float DeltaTime) override;
};
