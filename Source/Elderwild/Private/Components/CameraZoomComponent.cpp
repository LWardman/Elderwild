#include "Components/CameraZoomComponent.h"

#include "Camera/CameraComponent.h"
#include "Logging/ControlsLog.h"

UCameraZoomComponent::UCameraZoomComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCameraZoomComponent::ZoomCamera(float Direction)
{
    TargetFieldOfView -= Direction * 2;
    TargetFieldOfView = FMath::Clamp(TargetFieldOfView, MinimumFieldOfView, MaximumFieldOfView);
    UE_LOG(ControlsLog, Display, TEXT("Setting new target FOV: %f"), TargetFieldOfView);
}

void UCameraZoomComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    InterpolateCameraFieldOfView(DeltaTime);
}

void UCameraZoomComponent::InterpolateCameraFieldOfView(float DeltaTime)
{
    if (!Camera || TargetFieldOfView == FieldOfView) return;    

    const float FieldOfViewDelta = TargetFieldOfView - FieldOfView;
    const float InterpSpeed = FMath::Abs(FieldOfViewDelta);
    FieldOfView = FMath::FInterpTo(FieldOfView, TargetFieldOfView, DeltaTime, InterpSpeed);
    Camera->SetFieldOfView(FieldOfView);
}
