#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"

UCLASS()
class ELDERWILD_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* Click;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* Rotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* DragMoveCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* DragRotateCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* RotateBuilding;
};