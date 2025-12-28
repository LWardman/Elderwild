#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CameraZoomComponent.generated.h"

UCLASS(ClassGroup=Camera)
class ELDERWILD_API UCameraZoomComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    void ZoomCamera(float Direction);

protected:
    virtual void OnRegister() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
    UPROPERTY(Transient)
    UCameraComponent* Camera;

    float FieldOfView = 80;
    float TargetFieldOfView = FieldOfView;
    float MinimumFieldOfView = 16.0f;
    float MaximumFieldOfView = 90.0f;

	void InterpolateCameraFieldOfView(float DeltaTime);
};