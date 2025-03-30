#pragma once

typedef int32 Significance;
typedef float Probability;

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
	float Mean = 10.f;
	float StandardDeviation = 2.f;
	float Variance = StandardDeviation * StandardDeviation;
	
	float Current = Mean;

	void InitializeProbabilityMap();
	TMap<Significance, Probability> EntityProbability;
	
	FTimerHandle UpdateEntityTimer;

	void UpdateEntity();
};
