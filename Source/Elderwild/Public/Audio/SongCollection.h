#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SongCollection.generated.h"

UCLASS(BlueprintType)
class ELDERWILD_API USongCollection : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Music")
	TSet<USong*> Songs;
};
