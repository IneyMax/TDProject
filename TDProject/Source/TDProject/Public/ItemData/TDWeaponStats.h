#pragma once

#include "TDWeaponStats.generated.h"

class UTDItem;

USTRUCT(BlueprintType)
struct TDPROJECT_API FTDWeaponStats
{
	GENERATED_BODY()

	FTDWeaponStats()
	: ShotsDelay(1),
	SeriesDelay(1),
	ReloadTime(1),
	ShotInSeries(1),
	ShopCapacity(1)
	{}

	FTDWeaponStats(float InShotsDelay, float InSeriesDelay, float InReloadTime, int32 InShotInSeries, int32 InShopCapacity)
	: ShotsDelay(InShotsDelay),
	SeriesDelay(InSeriesDelay),
	ReloadTime(InReloadTime),
	ShotInSeries(InShotInSeries),
	ShopCapacity(InShopCapacity)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float ShotsDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float SeriesDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 ShotInSeries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 ShopCapacity;
};


