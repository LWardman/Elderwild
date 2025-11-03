#include "Creatures/Trader/Trader.h"

#include "Kismet/GameplayStatics.h"

#include "Components/FacingWidgetComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Creatures/Trader/TradeWidget.h"
#include "Player/PlayerPawn.h"
#include "Player/CameraController.h"
#include "Player/Input/CursorInteractor.h"
#include "Player/Input/MouseMode.h"
#include "Player/Input/InspectMode.h"

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
	FetchAndSubscribeToMouseEvents();
}

void ATrader::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (Icon)
		Icon->SetVisibility(PlayerIsInInspectMode());
}

void ATrader::BeginTraderInteraction(AActor* Actor, FKey Key)
{
	if (!PlayerIsInInspectMode()) return;
	
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

bool ATrader::PlayerIsInInspectMode() const
{
	if (MouseMode.IsValid())
	{
		return MouseMode->IsA(UInspectMode::StaticClass());
	}
	return false;
}

void ATrader::FetchAndSubscribeToMouseEvents()
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;
	
	const ACameraController* CamController = Cast<ACameraController>(PC);
	if (!CamController) return;
	
	UCursorInteractor* CursorInteractor = CamController->CursorInteractor;
	if (!CursorInteractor) return;
	
	CursorInteractor->OnMouseModeChanged.AddDynamic(this, &ATrader::OnMouseModeChanged);
	MouseMode = CursorInteractor->GetMouseMode();
}

void ATrader::OnMouseModeChanged(UMouseMode* NewMouseMode)
{
	MouseMode = NewMouseMode;
}
