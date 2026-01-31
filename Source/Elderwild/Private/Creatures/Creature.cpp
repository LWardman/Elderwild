#include "Creatures/Creature.h"

#include "Kismet/GameplayStatics.h"

#include "Calendar/Calendar.h"
#include "GameModes/DevGameMode.h"
#include "Creatures/CreatureController.h"

ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();
}

void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ACreatureController* AI = Cast<ACreatureController>(GetController()))
	{
		UE_LOG(LogTemp, Display, TEXT("bShouldBeSleeping: %s"), ShouldBeSleeping() ? TEXT("true") : TEXT("false"));
		AI->UpdateSleepState(ShouldBeSleeping());
	}
}

void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACreature::ShouldBeSleeping()
{
	ADevGameMode* GM = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GM || !GM->GetCalendar()) return false;
	
	return SleepsDuringTime == GM->GetCalendar()->GetDayState();
}
