#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CameraZoomComponent.generated.h"

class UCameraComponent;

UCLASS(ClassGroup=Camera)
class ELDERWILD_API UCameraZoomComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UCameraZoomComponent();
    
    void ZoomCamera(float Direction);
    
    void Init(UCameraComponent* InCamera) { Camera = InCamera; }

protected:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
    UPROPERTY(Transient)
    UCameraComponent* Camera;

    float FieldOfView = 80.0f;
    float TargetFieldOfView = 80.0f;
    float MinimumFieldOfView = 16.0f;
    float MaximumFieldOfView = 90.0f;

	void InterpolateCameraFieldOfView(float DeltaTime);
};