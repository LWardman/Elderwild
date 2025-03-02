#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ElderwildController.generated.h"

class UInputMappingContext;
class UInputAction;

/** Controller intended only for use with the player pawn
 */
UCLASS()
class ELDERWILD_API AElderwildController : public APlayerController
{
	GENERATED_BODY()

public:
	AElderwildController();

	// TODO : configure the mapping context and its InputActions 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ClickAction;

protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	void OnClickStarted();
};
