#include "Audio/DiskJockey.h"

#include "Audio/MusicSubsystem.h"
#include "Audio/Song.h"
#include "Logging/AudioLog.h"

void UDiskJockey::Start()
{
	UMusicSubsystem* MusicSubsystem = UMusicSubsystem::Get(this);
	if (AllSongs.IsEmpty() || !MusicSubsystem) return;

	GenreToPlaylistMap.Reset();
	GenreToPlaylistMap.Add(ESongGenre::Epic, EpicPlaylist);
	GenreToPlaylistMap.Add(ESongGenre::Happy, HappyPlaylist);
	GenreToPlaylistMap.Add(ESongGenre::Relaxing, RelaxingPlaylist);
	GenreToPlaylistMap.Add(ESongGenre::Sad, SadPlaylist);

	SplitPlaylistIntoPools();
	SetActivePlaylist(CurrentGenre);
	PlayNextSong();
}

void UDiskJockey::SplitPlaylistIntoPools()
{
	EpicPlaylist.Reset();
	HappyPlaylist.Reset();
	RelaxingPlaylist.Reset();
	SadPlaylist.Reset();

	for (USong* Song : AllSongs)
	{
		PutSongIntoPool(Song);
	}
}

void UDiskJockey::PutSongIntoPool(USong* Song)
{
	if (!Song) return;
	TArray PossibleGenres = {ESongGenre::Epic, ESongGenre::Happy, ESongGenre::Relaxing, ESongGenre::Sad};
	
	for (const ESongGenre Genre : PossibleGenres)
	{
		if (Song->IsOfGenre(Genre))
		{
			GenreToPlaylistMap[Genre].Add(Song);
		}
	}
}

void UDiskJockey::FeedSongToMusicSubsystem(const USong* Song)
{
	UMusicSubsystem* MusicSubsystem = UMusicSubsystem::Get(this);
	if (!Song || !MusicSubsystem) return;

	if (USoundBase* SoundBase = Song->GetSound())
	{
		MusicSubsystem->PlayMusic(SoundBase);
	}
}

void UDiskJockey::SetTimerForSongDuration(const USong* Song)
{
	UWorld* World = GetWorld();
	if (!World || !Song) return;

	float SongDuration = Song->GetSongDuration();

	World->GetTimerManager().SetTimer(SongTimer,
										this,
										&UDiskJockey::PlayNextSong,
										SongDuration,
										false);
}

void UDiskJockey::PlayNextSong()
{
	UE_LOG(AudioLog, Display, TEXT("Playing next song."));
	USong* Song = CurrentSongQueue.Pop();

	if (!Song)
	{
		SetActivePlaylist(CurrentGenre);
	}
	
	FeedSongToMusicSubsystem(Song);
	SetTimerForSongDuration(Song);
}

void UDiskJockey::SetActivePlaylist(ESongGenre Genre)
{
	TSet<USong*> Playlist = GenreToPlaylistMap[Genre];
	CurrentSongQueue.Empty();

	for (USong* Song : Playlist)
	{
		CurrentSongQueue.Add(Song);
	}
	ShuffleActivePlaylist();
}

void UDiskJockey::ShuffleActivePlaylist()
{
	const int32 LastIndex = CurrentSongQueue.Num() - 1;
	for (int32 i = 0; i < LastIndex; ++i)
	{
		int32 Index = FMath::RandRange(0, LastIndex);
		if (i != Index)
		{
			CurrentSongQueue.Swap(i, Index);
		}
	}
}
