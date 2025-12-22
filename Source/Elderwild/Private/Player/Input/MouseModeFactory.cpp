#include "Player/Input/MouseModeFactory.h"

#include "Player/Input/MouseMode.h"
#include "Player/Input/BuildMode.h"
#include "Player/Input/InspectMode.h"
#include "Player/Input/DialogueMode.h"

TSubclassOf<UMouseMode> UMouseModeFactory::GetModeClass(EMouseModeType Type)
{
    switch (Type)
    {
    case EMouseModeType::Build:   
        return UBuildMode::StaticClass();

    case EMouseModeType::Dialogue:
        return UDialogueMode::StaticClass();

    case EMouseModeType::Inspect: 
        return UInspectMode::StaticClass();

    default:                      
        UE_LOG(LogTemp, Error, TEXT("Passed in a wrong mouse type: %d"), (int)Type);
        return UMouseMode::StaticClass();
    }
}

UMouseMode* UMouseModeFactory::Create(UObject* Outer, EMouseModeType Type)
{
    TSubclassOf<UMouseMode> ModeClass = GetModeClass(Type);
    if (!ModeClass) return nullptr;
    return NewObject<UMouseMode>(Outer, ModeClass);
}
