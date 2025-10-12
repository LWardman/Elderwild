#include "Creatures/Trader/Trader.h"

#include "Kismet/GameplayStatics.h"

#include "Components/FacingWidgetComponent.h"
#include "Components/InventoryComponent.h"
#include "Creatures/Trader/TradeWidget.h"
#include "Player/PlayerPawn.h"

ATrader::ATrader()
{
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	
	Icon = CreateDefaultSubobject<UFacingWidgetComponent>(TEXT("Icon"));
	Icon->SetupAttachment(RootComponent);
	Icon->SetVisibility(true);
	Icon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Icon->SetDrawSize(FVector2D(64.f, 64.f));
}

void ATrader::BeginPlay()
{
	Super::BeginPlay();
	
	OnClicked.AddDynamic(this, &ATrader::BeginTraderInteraction);
}

void ATrader::BeginTraderInteraction(AActor* Actor, FKey Key)
{
	UE_LOG(LogTemp, Display, TEXT("Beginning Trade Interaction"));
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (TradeWidgetClass && PlayerController && !UTradeWidget::TradeWidgetExists())
	{
		TradeWidget = CreateWidget<UTradeWidget>(PlayerController, TradeWidgetClass);
			
		if (!TradeWidget)
		{
			UE_LOG(LogTemp, Error, TEXT("TradeWidget failed during creation"));
		}

		UInventoryComponent* PlayerInventory = nullptr;
			
		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(PlayerController->GetPawn()))
		{
			PlayerInventory = PlayerPawn->Inventory;
		}
		// Only add the widget to the screen if both sides have a valid inventory
		if (InventoryComponent && PlayerInventory)
		{
			UTradeWidget::SetTradeWidget(TradeWidget);
			TradeWidget->InitializeInventories(InventoryComponent, PlayerInventory);
			TradeWidget->AddToPlayerScreen();
		}
	}
}
