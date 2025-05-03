#include "Creatures/CreatureBase.h"


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
}

void ACreatureBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
