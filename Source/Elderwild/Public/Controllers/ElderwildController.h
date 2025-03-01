#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ElderwildController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ELDERWILD_API AElderwildController : public APlayerController
{
	GENERATED_BODY()

public:
	AElderwildController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClickAction;

protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	void OnClickStarted();
};
