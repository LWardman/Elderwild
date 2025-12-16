#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MusicSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMusicSettingsUpdated, const UMusicSettings*, UpdatedMusicSettings);

class USongCollection;

UCLASS(Config=Game, DefaultConfig)
class ELDERWILD_API UMusicSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Music Settings Events")
	FMusicSettingsUpdated MusicSettingsUpdated;
	
	// Find the settings under Project Settings -> Game -> Music
	virtual FName GetCategoryName() const override { return "Game"; }

	// Any setting fetched through this is read-only
	static const UMusicSettings* Get() { return GetDefault<UMusicSettings>(); }

	UPROPERTY(Config, EditAnywhere, Category="Music")
	TSoftObjectPtr<USoundClass> MusicSoundClass;
	
	UPROPERTY(Config, EditAnywhere, Category="Music")
	TSoftObjectPtr<USongCollection> DefaultPlaylist = nullptr;

	UPROPERTY(Config, EditAnywhere, Category="Music", meta=(ClampMin="0.0", ClampMax="1.0"))
	float MusicVolume;

	static void SetMusicVolume(float NewVolume)
	{
		UMusicSettings* Settings = GetMutableDefault<UMusicSettings>();
		Settings->MusicVolume = FMath::Clamp(NewVolume, 0.0f, 1.0f);
		Settings->SaveConfig();

		Settings->MusicSettingsUpdated.Broadcast(Settings);
	}
};
