#include "Buildings/Components/InhabitanceComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Buildings/House.h"
#include "Creatures/Creature.h"
#include "Creatures/Components/ResidentComponent.h"
#include "Logging/BuildingLog.h"

UInhabitanceComponent::UInhabitanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
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
	
	if (HasSpace() && ShouldAutomaticallyPopulate())
	{
		RegisterPotentialInhabitants();
	}
}

bool UInhabitanceComponent::RegisterInhabitant(AActor* NewInhabitant)
{
	if (!HasSpace()) return false;	
	
	InhabitingCreatures.Add(NewInhabitant);
	return true;
}

void UInhabitanceComponent::RegisterPotentialInhabitants()
{
	if (!Parent)
	{
		UE_LOG(BuildingLog, Warning, TEXT("Inhabitance Component has no House Parent"));
		return;
	}
	
	// TODO : Cache homeless creatures somewhere as this will get expensive for large amounts of creatures
	TArray<AActor*> Creatures;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreature::StaticClass(), Creatures);
	
	UE_LOG(BuildingLog, Display, TEXT("Building found %i creatures to check"), Creatures.Num());

	for (AActor* Creature : Creatures)
	{
		if (IsFull()) break;
		
		UResidentComponent* ResidentComponent = Creature->FindComponentByClass<UResidentComponent>();
		
		if (!ResidentComponent)
		{
			UE_LOG(BuildingLog, Display, TEXT("Creature %s has no resident component"), *Creature->GetName());
			continue;
		}
		if (ResidentComponent->HasHome())
		{
			UE_LOG(BuildingLog, Display, TEXT("Skipping Creature %s because it already has a home"), *Creature->GetName());
			continue;
		}
		
		UE_LOG(BuildingLog, Display, TEXT("Assigning home %s to creature %s"), *Parent->GetName(), *Creature->GetName());
		ResidentComponent->AssignToHouse(Parent);
		RegisterInhabitant(Creature);
	}
}