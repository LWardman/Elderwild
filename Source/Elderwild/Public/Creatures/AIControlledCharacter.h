#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIControlledCharacter.generated.h"


UCLASS()
class ELDERWILD_API AAIControlledCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAIControlledCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
