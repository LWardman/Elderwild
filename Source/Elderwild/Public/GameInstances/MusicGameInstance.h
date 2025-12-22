#pragma once

#include "CoreMinimal.h"
#include "ElderwildGameInstance.h"
#include "MusicGameInstance.generated.h"

UCLASS()
class ELDERWILD_API UMusicGameInstance : public UElderwildGameInstance
{
	GENERATED_BODY()

public:
	virtual void OnStart() override;
};
