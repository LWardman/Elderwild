#pragma once

#include "CoreMinimal.h"
#include "Song.h"
#include "DiskJockey.generated.h"

class USong;
enum class ESongGenre : uint8;

/**
 *	Feeds songs into the music subsystem.
 */
UCLASS()
class ELDERWILD_API UDiskJockey : public UObject
{
	GENERATED_BODY()

public:
	void Start();

	void SetPlaylist(const TSet<USong*>& NewPlaylist) { AllSongs = NewPlaylist; }
	
private:
	UPROPERTY(EditAnywhere, Category="Songs", meta=(AllowPrivateAccess))
	TSet<USong*> AllSongs;

	void SplitPlaylistIntoPools();
	void PutSongIntoPool(USong* Song);

	UPROPERTY()
	TSet<USong*> EpicPlaylist;
	
	UPROPERTY()
	TSet<USong*> HappyPlaylist;
	
	UPROPERTY()
	TSet<USong*> RelaxingPlaylist;
	
	UPROPERTY()
	TSet<USong*> SadPlaylist;
	
	TMap<ESongGenre, TSet<USong*>> GenreToPlaylistMap;

	void FeedSongToMusicSubsystem(const USong* Song);

	void SetTimerForSongDuration(const USong* Song);

	FTimerHandle SongTimer;

	UFUNCTION()
	void PlayNextSong();

	UPROPERTY()
	TArray<USong*> CurrentSongQueue;

	ESongGenre CurrentGenre = ESongGenre::Relaxing;

	void SetActivePlaylist(ESongGenre Genre);
	void ShuffleActivePlaylist();
};
