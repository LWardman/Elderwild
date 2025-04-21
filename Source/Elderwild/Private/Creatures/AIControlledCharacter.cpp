#include "Creatures/AIControlledCharacter.h"


AAIControlledCharacter::AAIControlledCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIControlledCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAIControlledCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIControlledCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

