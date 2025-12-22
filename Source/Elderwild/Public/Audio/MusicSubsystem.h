#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MusicSubsystem.generated.h"

class UMusicSettings;
class UDiskJockey;

/**
 * Use " UMusicSubsystem* MusicSubsystem = UMusicSubsystem::Get(this) " to retrieve the system
 */
UCLASS()
class ELDERWILD_API UMusicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UMusicSubsystem* Get(UObject* WorldContextObject);

	// Subsystem lifecycle
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// API
	void PlayMusic(USoundBase* MusicTrack);
	void StopMusic();
	bool IsPlaying() const;

	UDiskJockey* GetDJ();

private:
	void EnsureAudioComponent();
	void EnsureDiskJockey();
	void AdjustAudioComponentToMusicSettings(const UMusicSettings* MusicSettings);
	void SubscribeToMusicSettings();
	
	UFUNCTION()
	void OnMusicSettingsUpdated(const UMusicSettings* NewSettings);

	UPROPERTY(Transient)
	UAudioComponent* AudioComponent = nullptr;
	
	UPROPERTY()
	UDiskJockey* DJ;
};
