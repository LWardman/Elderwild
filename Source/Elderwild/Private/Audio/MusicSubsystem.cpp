#include "Audio/MusicSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

#include "Audio/DiskJockey.h"
#include "Audio/MusicSettings.h"
#include "Components/AudioComponent.h"
#include "Logging/AudioLog.h"


UMusicSubsystem* UMusicSubsystem::Get(UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	return GameInstance ? GameInstance->GetSubsystem<UMusicSubsystem>() : nullptr;
}

void UMusicSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMusicSubsystem::Deinitialize()
{
	if (AudioComponent)
	{
		AudioComponent->Stop();
		AudioComponent->DestroyComponent();
		AudioComponent = nullptr;
	}

	Super::Deinitialize();
}

void UMusicSubsystem::PlayMusic(USoundBase* MusicTrack)
{
	if (!MusicTrack)
	{
		UE_LOG(AudioLog, Warning, TEXT("MusicTrack is null"));
		return;
	}

	EnsureAudioComponent();
	if (!AudioComponent) return;

	if (AudioComponent->IsPlaying() && AudioComponent->Sound == MusicTrack) return;

	AudioComponent->SetSound(MusicTrack);
	const UMusicSettings* MusicSettings = UMusicSettings::Get(); 
	AdjustAudioComponentToMusicSettings(MusicSettings);
	AudioComponent->Play();
}

void UMusicSubsystem::StopMusic()
{
	if (AudioComponent && AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}
}

bool UMusicSubsystem::IsPlaying() const
{
	return AudioComponent && AudioComponent->IsPlaying();
}

UDiskJockey* UMusicSubsystem::GetDJ()
{
	EnsureDiskJockey();
	return DJ;
}

void UMusicSubsystem::EnsureAudioComponent()
{
	if (AudioComponent && AudioComponent->IsValidLowLevel()) return;

	UWorld* World = GetWorld();
	if (!World || !World->IsGameWorld())
	{
		UE_LOG(AudioLog, Warning, TEXT("MusicSubsystem: No world available to create AudioComponent"));
		return;
	}

	AWorldSettings* WorldSettings = World->GetWorldSettings();
	AudioComponent = NewObject<UAudioComponent>(WorldSettings);
	if (!AudioComponent)
	{
		UE_LOG(AudioLog, Warning, TEXT("MusicSubsystem: Failed to create AudioComponent"));
		return;
	}

	AudioComponent->bAutoActivate = true;
	AudioComponent->bIsUISound = false;
	AudioComponent->RegisterComponent();
}

void UMusicSubsystem::EnsureDiskJockey()
{
	if (DJ) return;
	
	UWorld* World = GetWorld();
	if (!World || !World->IsGameWorld())
	{
		UE_LOG(AudioLog, Warning, TEXT("MusicSubsystem: No world available to create DJ"));
		return;
	}
	
	AWorldSettings* WorldSettings = World->GetWorldSettings();
	UDiskJockey* NewDJ = NewObject<UDiskJockey>(WorldSettings);

	if (!NewDJ)
	{
		UE_LOG(AudioLog, Warning, TEXT("MusicSubsystem: Failed to create a DJ"));
		return;
	}

	DJ = NewDJ;
}

void UMusicSubsystem::AdjustAudioComponentToMusicSettings(const UMusicSettings* MusicSettings)
{
	if (AudioComponent && MusicSettings)
	{
		UE_LOG(AudioLog, Display, TEXT("MusicSubsystem: Setting Music volume: %f"), MusicSettings->MusicVolume);
		AudioComponent->VolumeMultiplier = MusicSettings->MusicVolume;
		if (const TObjectPtr<USoundClass> SoundClass = MusicSettings->MusicSoundClass.LoadSynchronous())
		{
			AudioComponent->SoundClassOverride = SoundClass;
		}
	}
}

void UMusicSubsystem::SubscribeToMusicSettings()
{
	if (UMusicSettings* MusicSettings = GetMutableDefault<UMusicSettings>())
	{
		MusicSettings->MusicSettingsUpdated.AddDynamic(this, &UMusicSubsystem::OnMusicSettingsUpdated);
	}
}

void UMusicSubsystem::OnMusicSettingsUpdated(const UMusicSettings* NewSettings)
{
	EnsureAudioComponent();
	AdjustAudioComponentToMusicSettings(NewSettings);
}
