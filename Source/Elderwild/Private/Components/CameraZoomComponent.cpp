#include "Components/CameraZoom.h"

void UCameraZoom::ZoomCamera(float Direction)
{
    TargetFieldOfView -= Direction * 2;
    TargetFieldOfView = FMath::Clamp(TargetFieldOfView, MinimumFieldOfView, MaximumFieldOfView);
}

void UCameraZoom::OnRegister()
{
    Super::OnRegister();

    Camera = Cast<UCameraComponent>(GetAttachParent());
}

void UCameraZoom::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    InterpolateCameraFieldOfView(DeltaTime);
}

void UCameraZoom::InterpolateCameraFieldOfView(float DeltaTime)
{
    if (!Camera) return;    

    const float FieldOfViewDelta = TargetFieldOfView - FieldOfView;
    const float InterpSpeed = FMath::Abs(FieldOfViewDelta);
    FieldOfView = FMath::FInterpTo(FieldOfView, TargetFieldOfView, DeltaTime, InterpSpeed);
    Camera->SetFieldOfView(FieldOfView);
}
