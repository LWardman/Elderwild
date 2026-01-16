#pragma once

#include "Player/Input/DraggingMousePositions.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CameraTranslationComponent.generated.h"

class UControlledCamera;

UCLASS(ClassGroup=Camera)
class ELDERWILD_API UCameraTranslationComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UCameraTranslationComponent();

    void Init(UControlledCamera* InCamera) { Camera = InCamera; }
    
    void BeginDragMovement(FVector2D Cursor) { DragTranslation.ResetToCursorsPosition(Cursor); }
    void DragMove(FVector2d Cursor);

private:
    FVector UpdateMousePositionsAndGetDelta(FDraggingMousePositions& CursorPositions, const FVector2d Cursor);

    FDraggingMousePositions DragTranslation;

    UPROPERTY(Transient)
    UControlledCamera* Camera;
};
