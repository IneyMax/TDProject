// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItem.h"
#include "Item/Weapon/TDWeaponBase.h"
#include "TDProject/Public/TDAssetManager.h"
#include "TDItemWeapon.generated.h"

/**
 * 
 */

UCLASS()
class TDPROJECT_API UTDItemWeapon : public UTDItem
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	UTDItemWeapon()
	{
		ItemType = UTDAssetManager::WeaponItemType;
	}
	
	/** Weapon actor to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TSubclassOf<ATDWeaponBase> WeaponClass;
};
