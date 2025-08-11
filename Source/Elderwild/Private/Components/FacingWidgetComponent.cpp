#include "Components/FacingWidgetComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"

UFacingWidgetComponent::UFacingWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetWidgetSpace(EWidgetSpace::World);
	SetTwoSided(true);
	SetDrawAtDesiredSize(true);
	SetPivot(FVector2D(0.5f, 1.0f));
	BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetCastShadow(false);
}

void UFacingWidgetComponent::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	if (GetWidgetSpace() != EWidgetSpace::World)
	{
		SetWidgetSpace(EWidgetSpace::World);
	}
}

void UFacingWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceUpdate += DeltaTime;
	if (UpdateInterval > 0.f && TimeSinceUpdate < UpdateInterval)
	{
		return;
	}
	TimeSinceUpdate = 0.0;

	UpdateFacing();
}

void UFacingWidgetComponent::UpdateFacing()
{
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC) return;

	APlayerCameraManager* PCM = PC->PlayerCameraManager;
	if (!PCM) return;

	const FVector IconLoc = GetComponentLocation();
	const FVector CamLoc  = PCM->GetCameraLocation();

	// Optional distance cull
	if (MaxVisibleDistance > 0.f)
	{
		const float DistSq = FVector::DistSquared(IconLoc, CamLoc);
		const bool Visible = DistSq <= FMath::Square(MaxVisibleDistance);
		if (IsVisible() != Visible)
		{
			SetVisibility(Visible, true);
		}
		if (!Visible) return;
	}

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(IconLoc, CamLoc);

	FRotator FinalRot;
	if (bYawOnly)
	{
		FinalRot = FRotator(0.f, LookAt.Yaw, 0.f);
	}
	else
	{
		float Pitch = LookAt.Pitch;
		if (bClampPitch)
		{
			Pitch = FMath::ClampAngle(Pitch, MinPitch, MaxPitch);
		}
		FinalRot = FRotator(Pitch, LookAt.Yaw, 0.f);
	}

	SetWorldRotation(FinalRot);
}
