#include "Creatures/CreatureBase.h"

#include "Kismet/GameplayStatics.h"

#include "Calendar/Calendar.h"
#include "GameModes/DevGameMode.h"

ACreatureBase::ACreatureBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACreatureBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACreatureBase::Tick(float DeltaTime)
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

void ACreatureBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACreatureBase::AssignToHouse(AHouse* NewHouse)
{
	House = NewHouse;
}

void ACreatureBase::RemoveFromHouse()
{
	House = nullptr;
}

bool ACreatureBase::HasAHome()
{
	return House != nullptr;
}

bool ACreatureBase::ShouldBeSleeping()
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);

	ADevGameMode* DevGameMode = Cast<ADevGameMode>(GM);

	if (!DevGameMode) return false;
	if (!DevGameMode->GetCalendar()) return false;
	
	EDayNight CurrentDayState = DevGameMode->GetCalendar()->GetDayState();

	return SleepsDuringTime == CurrentDayState;
}
