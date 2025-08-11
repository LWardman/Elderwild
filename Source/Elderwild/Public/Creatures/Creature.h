#pragma once

#include "Calendar/DayCycler.h" // TODO : move EDayNight to its own file.

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

class AHouse;

enum class EDayNight : uint8;

UCLASS()
class ELDERWILD_API ACreature : public ACharacter
{
	GENERATED_BODY()

public:
	ACreature();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	EDayNight SleepsDuringTime = EDayNight::Day;

	// TODO : make this respond to DayCycler events instead?
	bool ShouldBeSleeping();
	
};
