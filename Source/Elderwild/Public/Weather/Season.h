#pragma once

typedef float Temperature;
typedef float WindSpeed;
typedef float Percentage;

UCLASS()
class ELDERWILD_API USeason : public UObject
{
	GENERATED_BODY()

public:
	USeason();

private:
	int32 NumberOfDays = 20;
	
	Temperature TargetTemp = 10.f;
	WindSpeed TargetWind = 10.f;
	Percentage TargetRainfall = 10.f;

	Temperature CurrentTemp = TargetTemp;
	WindSpeed CurrentWind = TargetWind;
	Percentage CurrentRainfall = TargetRainfall;
};
