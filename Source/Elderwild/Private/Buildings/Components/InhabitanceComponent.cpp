#include "Buildings/Components/InhabitanceComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Creatures/Resident.h"
#include "Buildings/House.h"

UInhabitanceComponent::UInhabitanceComponent()
{
	InhabitingCreatures.Reserve(GetMaxInhabitants());
}

void UInhabitanceComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Parent = Cast<AHouse>(GetOwner());
}

void UInhabitanceComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (HasSpace())
	{
		RegisterPotentialInhabitants();
	}
}

bool UInhabitanceComponent::RegisterInhabitant(ACreature* NewInhabitant)
{
	if (!HasSpace()) return false;	
	
	InhabitingCreatures.Add(NewInhabitant);
	return true;
}

void UInhabitanceComponent::RegisterPotentialInhabitants()
{
	// TODO : Cache homeless creatures somewhere as this will get expensive for large amounts of creatures
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreature::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (IsFull()) break;
		
		if (AResident* Resident = Cast<AResident>(Actor))
		{
			if (Resident->HasAHome()) continue;
			
			if (Parent) Resident->AssignToHouse(Parent);
			RegisterInhabitant(Resident);
		}
	}	
}
