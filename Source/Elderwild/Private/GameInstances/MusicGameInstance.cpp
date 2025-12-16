#include "GameInstances/MusicGameInstance.h"

#include "Audio/MusicSubsystem.h"
#include "Audio/DiskJockey.h"
#include "Audio/SongCollection.h"
#include "Audio/MusicSettings.h"

void UMusicGameInstance::OnStart()
{
	Super::Init();

	const UMusicSettings* MusicSettings = UMusicSettings::Get();
	UMusicSubsystem* MusicSubsystem = UMusicSubsystem::Get(this);
	if (!MusicSettings || !MusicSubsystem) return;
	
	if (TSoftObjectPtr<USongCollection> DefaultPlaylist = MusicSettings->DefaultPlaylist)
	{
		if (UDiskJockey* DJ = MusicSubsystem->GetDJ())
		{
			DJ->SetPlaylist(DefaultPlaylist->Songs);
			DJ->Start();
		}
	}
}
