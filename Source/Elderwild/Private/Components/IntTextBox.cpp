#include "Components/IntTextBox.h"

void UIntTextBox::SetIntText(int32 InValue)
{
	FString StringFromInt = FString::FromInt(InValue);
	FText TextFromString = FText::FromString(StringFromInt);
	SetText(TextFromString);
}

