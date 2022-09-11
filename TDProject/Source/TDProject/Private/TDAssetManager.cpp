// Fill out your copyright notice in the Description page of Project Settings.

#include "TDProject/Public/TDAssetManager.h"

#include "TDProject/TDProject.h"

const FPrimaryAssetType	UTDAssetManager::AmplifierItemType = TEXT("Amplifier");
const FPrimaryAssetType	UTDAssetManager::AmmoItemType = TEXT("Ammo");
const FPrimaryAssetType	UTDAssetManager::WeaponItemType = TEXT("Weapon");

void UTDAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}

UTDItem* UTDAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UTDItem* LoadedItem = Cast<UTDItem>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTDProject, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}

UTDAssetManager& UTDAssetManager::Get()
{
	UTDAssetManager* This = Cast<UTDAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTDProject, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be RPGAssetManager!"));
		return *NewObject<UTDAssetManager>(); // never calls this
	}
}


