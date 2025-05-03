#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatureBase.generated.h"

class ACreatureController;

UCLASS()
class ELDERWILD_API ACreatureBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACreatureBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
