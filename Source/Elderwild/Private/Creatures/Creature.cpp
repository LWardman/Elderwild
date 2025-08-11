#include "Creatures/Creature.h"

#include "Kismet/GameplayStatics.h"

#include "Calendar/Calendar.h"
#include "GameModes/DevGameMode.h"

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

	if (ShouldBeSleeping())
	{
		//UE_LOG(LogTemp, Display, TEXT("Should be sleeping"));
	}
	else
	{
		//UE_LOG(LogTemp, Display, TEXT("Should be working"));
	}
}

void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACreature::ShouldBeSleeping()
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);

	ADevGameMode* DevGameMode = Cast<ADevGameMode>(GM);

	if (!DevGameMode) return false;
	if (!DevGameMode->GetCalendar()) return false;
	
	EDayNight CurrentDayState = DevGameMode->GetCalendar()->GetDayState();

	return SleepsDuringTime == CurrentDayState;
}
