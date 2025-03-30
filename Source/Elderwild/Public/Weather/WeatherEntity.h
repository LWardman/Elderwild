#pragma once

/* Weather Entities are things like Temperature, Wind Speed, Rainfall etc.
 *
 * These entities follow a random walk weighed towards what the season
 * dictates should be the average value.
 */
UCLASS()
class ELDERWILD_API UWeatherEntity : public UObject
{
	GENERATED_BODY()
	
public:
	UWeatherEntity();

private:
	float Target = 10.f;
	float Current = Target;
};
