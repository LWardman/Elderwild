#pragma once
#include "CoreMinimal.h"
#include "MouseModeTypes.h"
#include "MouseModeFactory.generated.h"

class UMouseMode;

UCLASS()
class ELDERWILD_API UMouseModeFactory : public UObject
{
    GENERATED_BODY()
public:
    static TSubclassOf<UMouseMode> GetModeClass(EMouseModeType Type);

    static UMouseMode* Create(UObject* Outer, EMouseModeType Type);
};
