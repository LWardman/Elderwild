#include "Weather/Season.h"

#include "Weather/WeatherEntity.h"

USeason::USeason()
{
	Temperature = CreateDefaultSubobject<UWeatherEntity>("Temperature");
	Wind = CreateDefaultSubobject<UWeatherEntity>("Wind");
	Rain = CreateDefaultSubobject<UWeatherEntity>("Rain");
}
