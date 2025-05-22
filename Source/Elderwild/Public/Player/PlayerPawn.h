#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UControlledCamera;
class UFloatingPawnMovement;
class AGrid;
class UDialogueComponent;

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
	UControlledCamera* Camera;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	UDialogueComponent* DialogueComponent;

	virtual void Tick(float DeltaTime) override;
};
