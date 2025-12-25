#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueInformation.generated.h"

UCLASS()
class ELDERWILD_API UDialogueInformation : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category="Variables")
    FText SpeakingCharacter = TEXT("UninitializedName");

    UPROPERTY(EditAnywhere, Category = "Variables")
    TArray<FText> LinesOfDialogue;

    FText GetLineFromNumber(int32 MessageNumber)
    {
        if (LineNumberIsValid(MessageNumber))
        {
            return LinesOfDialogue[MessageNumber];
        }
        return FText::GetEmpty();
    }

    int32 GetNumberOfLines() { return LinesOfDialogue.Num(); }

    bool LineNumberIsValid(int32 LineNumber) { return LinesOfDialogue.IsValidIndex(LineNumber); }

    bool HasMessages() { return LinesOfDialogue.Num() > 0; }

    FText GetLineNumberText(int32 LineNumber)
    {
        FString CurrentNumber = FString::FromInt(LineNumber + 1); // '+1' accounts for ints starting at 0
        FString SlideCount = FString::FromInt(GetNumberOfLines());
        FString FormattedSlideInformation = CurrentNumber + "/" + SlideCount;
        return FText::FromString(FormattedSlideInformation);
    }
};
