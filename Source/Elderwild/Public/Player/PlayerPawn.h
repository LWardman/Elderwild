#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"


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
	class UControlledCamera* Camera;

	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	class UDialogueComponent* DialogueComponent;

	UPROPERTY(EditAnywhere)
	class UInventoryComponent* Inventory;
	
	virtual void Tick(float DeltaTime) override;
};
