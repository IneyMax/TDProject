#pragma once

#include "CoreMinimal.h"
#include "TDAssetManager.h"
#include "TDItem.h"
#include "Item/Ammo/TDBulletBase.h"
#include "TDItemAmmo.generated.h"

/**
 * 
 */
UCLASS()
class TDPROJECT_API UTDItemAmmo : public UTDItem
{
	GENERATED_BODY()

public:
	/** Constructor */
	UTDItemAmmo()
	{
		ItemType = UTDAssetManager::WeaponItemType;
	}
	
	/** Ammo actor to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	TSubclassOf<ATDBulletBase> AmmoClass;
};
