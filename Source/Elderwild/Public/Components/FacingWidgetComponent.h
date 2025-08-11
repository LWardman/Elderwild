#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FacingWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class ELDERWILD_API UFacingWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFacingWidgetComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Facing")
	bool bYawOnly = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Facing", meta=(EditCondition="!bYawOnly"))
	bool bClampPitch = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Facing", meta=(EditCondition="!bYawOnly"))
	float MinPitch = -10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Facing", meta=(EditCondition="!bYawOnly"))
	float MaxPitch = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Facing")
	float MaxVisibleDistance = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Facing", meta=(ClampMin="0.0"))
	float UpdateInterval = 0.f;

protected:
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	double TimeSinceUpdate = 0.0;
	void UpdateFacing();	
};
