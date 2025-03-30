#pragma once

class UWeatherEntity;

UCLASS()
class ELDERWILD_API USeason : public UObject
{
	GENERATED_BODY()

public:
	USeason();

private:
	int32 NumberOfDays = 20;

	UPROPERTY()
	UWeatherEntity* Temperature;
	
	UPROPERTY()
	UWeatherEntity* Wind;
	
	UPROPERTY()
	UWeatherEntity* Rain;
};
