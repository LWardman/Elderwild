#include "Buildings/Building.h"

#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "Gridmap/Grid.h"
#include "Gridmap/GridDimensions.h"
#include "GameModes/DevGameMode.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	FindEntranceLocation();
	SpawnDebugSphereAtEntrance();
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::FindEntranceLocation()
{
	ADevGameMode* GameMode = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(this));
	
	if (!GameMode) return;
	
	AGrid* Grid = GameMode->GetGrid();
	if (!Grid || !Grid->GetGridDimensions()) return;

	int32 TileSize = Grid->GetGridDimensions()->GetTileSize();
	int32 HalfTileLength = TileSize / 2;
	int32 BuildingDepth = BuildingSize.Y;
	
	FVector ForwardVec = GetActorForwardVector();

	EntranceLocation = GetActorLocation() + ForwardVec * HalfTileLength * BuildingDepth;
}

void ABuilding::SpawnDebugSphereAtEntrance() const
{
	DrawDebugSphere(GetWorld(), EntranceLocation, 12, 10, FColor::Red, true);
}

