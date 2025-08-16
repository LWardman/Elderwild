#include "Creatures/Trader.h"

#include "Components/DucatPouch.h"
#include "Components/FacingWidgetComponent.h"

ATrader::ATrader()
{
	PrimaryActorTick.bCanEverTick = true;

	DucatPouch = CreateDefaultSubobject<UDucatPouch>(TEXT("Ducat Pouch"));
	
	Icon = CreateDefaultSubobject<UFacingWidgetComponent>(TEXT("Icon"));
	Icon->SetupAttachment(RootComponent);

	Icon->SetWidgetSpace(EWidgetSpace::World);
	Icon->SetDrawAtDesiredSize(true);
	Icon->SetPivot(FVector2D(0.5f, 1.0f)); // bottom center
	Icon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Icon->SetTwoSided(true);
	Icon->SetDrawSize(FVector2D(64.f, 64.f));
}
