#include "Weather/WeatherEntity.h"


UWeatherEntity::UWeatherEntity()
{
	InitializeProbabilityMap();
}

void UWeatherEntity::InitializeProbabilityMap()
{
	EntityProbability.Add(-5, 0.0f);
	EntityProbability.Add(-4, 0.02f);
	EntityProbability.Add(-3, 0.1f);
	EntityProbability.Add(-2, 0.2f);
	EntityProbability.Add(-1, 0.35f);
	EntityProbability.Add(0, 0.5f);
	EntityProbability.Add(1, 0.65f);
	EntityProbability.Add(2, 0.8f);
	EntityProbability.Add(3, 0.9f);
	EntityProbability.Add(4, 0.98f);
	EntityProbability.Add(-5, 1.0f);
}


void UWeatherEntity::UpdateEntity()
{
	float DistanceFromMean = Current - Mean;

	checkf(Variance != 0, TEXT("A weather entity should not have a variance of 0"));
	Significance ProbabilityKey = FMath::FloorToInt(DistanceFromMean / StandardDeviation);

	Probability ProbabilityValue = EntityProbability[ProbabilityKey];

	Probability RandomValue = FMath::RandRange(0.f, 1.f);

	if (ProbabilityValue > RandomValue)
	{
		Current += 1.f;
	}
	else
	{
		Current -= 1.f;
	}
}
