#pragma once
#include "MouseModeTypes.generated.h"

UENUM(BlueprintType)
enum class EMouseModeType : uint8
{
    Default UMETA(DisplayName="Default"),
    Build   UMETA(DisplayName="Build"),
    Inspect UMETA(DisplayName="Inspect"),
    Dialogue UMETA(DisplayName="Dialogue")
};
