#pragma once

#include "Calendar/DayCycler.h" // TODO : move EDayNight to its own file.

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatureBase.generated.h"

class AHouse;

enum class EDayNight : uint8;

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

	// TODO : Move to an interface?
	void AssignToHouse(AHouse* NewHouse);

	void RemoveFromHouse();

	bool HasAHome();

	EDayNight SleepsDuringTime = EDayNight::Day;

	// TODO : make this respond to DayCycler events instead?
	bool ShouldBeSleeping();
	
private:
	UPROPERTY()
	AHouse* House;
};
