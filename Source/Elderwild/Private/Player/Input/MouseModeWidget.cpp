#include "Player/Input/MouseModeWidget.h"

#include "Components/Button.h"

#include "Player/Input/CursorInteractor.h"
#include "Player/Input/MouseModeTypes.h"

void UMouseModeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InspectButton)
	{
		InspectButton->OnReleased.AddDynamic(this, &UMouseModeWidget::OnInspectButtonPressed);
	}
	if (DialogueButton)
	{
		DialogueButton->OnReleased.AddDynamic(this, &UMouseModeWidget::OnDialogueButtonPressed);
	}
}

void UMouseModeWidget::OnInspectButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Inspect mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(EMouseModeType::Inspect);
	}
}

void UMouseModeWidget::OnDialogueButtonPressed()
{
	UE_LOG(LogTemp, Display, TEXT("Dialogue mode"));
	if (CursorInteractor)
	{
		CursorInteractor->ChangeMouseMode(EMouseModeType::Dialogue);
	}
}

void UMouseModeWidget::SetCursorInteractor(UCursorInteractor* NewCursorInteractor)
{
	CursorInteractor = NewCursorInteractor;
}
