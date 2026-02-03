#include "Buildings/Building.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
