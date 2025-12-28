#pragma once

#include "Player/Input/DraggingMousePositions.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CameraTranslationComponent.generated.h"

UCLASS(ClassGroup=Camera)
class ELDERWILD_API UCameraTranslationComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UCameraTranslationComponent();

    void BeginDragMovement(FVector2D Cursor) { DragTranslation.ResetToCursorsPosition(Cursor); }
    void DragMove(FVector2d Cursor);

protected:
    virtual void OnRegister() override;

private:
    FVector UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor);

    FDraggingMousePositions DragTranslation;

    UPROPERTY(Transient)
    UCameraComponent* Camera;
};
