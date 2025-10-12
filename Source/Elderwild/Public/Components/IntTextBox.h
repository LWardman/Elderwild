#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "IntTextBox.generated.h"

UCLASS()
class ELDERWILD_API UIntTextBox : public UTextBlock
{
	GENERATED_BODY()

public:
	void SetIntText(int32 InValue);
	void SetIntText(float InValue) { SetIntText(static_cast<int32>(InValue)); }
};
