#pragma once

#include "CoreMinimal.h"
#include "Song.generated.h"

UENUM(BlueprintType)
enum class ESongGenre : uint8
{
	Epic UMETA(DisplayName = "Epic"),
	Relaxing UMETA(DisplayName = "Relaxing"),
	Sad UMETA(DisplayName = "Sad"),
	Happy UMETA(DisplayName = "Happy")
};

UCLASS(Blueprintable)
class ELDERWILD_API USong : public UDataAsset
{
	GENERATED_BODY()

public:
	TSet<ESongGenre> GetGenres() const { return Genres; }

	USoundBase* GetSound() const { return Sound; }
	
	bool IsOfGenre(const ESongGenre Genre) const { return Genres.Contains(Genre); }

	float GetSongDuration() const { return Sound ? Sound->Duration : 0; }

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	USoundBase* Sound;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
	TSet<ESongGenre> Genres;
};
