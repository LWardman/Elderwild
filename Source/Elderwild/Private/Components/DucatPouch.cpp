#include "Components/DucatPouch.h"

void UDucatPouch::MakePurchase(int32 PurchaseCost)
{
	if (CanAffordPurchase(PurchaseCost))
	{
		SubtractDucats(PurchaseCost);
	}
}

void UDucatPouch::AddDucats(int32 Amount)
{
	Ducats += Amount;
}

void UDucatPouch::SubtractDucats(int32 Amount)
{
	Ducats -= Amount;
}
