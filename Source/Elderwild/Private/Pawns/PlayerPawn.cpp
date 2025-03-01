#include "Pawns/PlayerPawn.h"

#include "Actors/Grid.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameMode.h"
#include "GameModes/DevGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APlayerPawn::APlayerPawn()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera...
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
	Camera->SetRelativeRotation(FRotator(-60, 0, 0));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult Hit;
		if (PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit))
		{
			FVector HitLocation = Hit.Location;
			FVector ImpactNormal = Hit.ImpactNormal;
			FRotator CursorRotation = UKismetMathLibrary::MakeRotationFromAxes(ImpactNormal, FVector::Zero(), FVector::Zero());
			
			
			if (ADevGameMode* GM = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
            {
	            if (AGrid* Grid = GM->GetGrid())
	            {
	            	int32 GridRow;
	            	int32 GridCol;
	            	bool IsValid;
		            Grid->LocationToTile(HitLocation, GridRow, GridCol, IsValid);
	            	Grid->SetSelectedTile(GridRow, GridCol);
	            }
            }
		}
		else // If nothing found under cursor
		{
			if (ADevGameMode* GM = Cast<ADevGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				if (AGrid* Grid = GM->GetGrid())
				{
					// Passing invalid row & tile to force no selection
					Grid->SetSelectedTile(-1, -1);
				}
			}
		}
	}
	
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
