#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ItemData/TDItem.h"
#include "TDAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TDPROJECT_API UTDAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	// Constructor and overrides
	UTDAssetManager() {}
	
	virtual void StartInitialLoading() override;

	/** Static types for items */
	static const FPrimaryAssetType	AmplifierItemType;
	static const FPrimaryAssetType	AmmoItemType;
	static const FPrimaryAssetType	WeaponItemType;

	/** Returns the current AssetManager object */
	static UTDAssetManager& Get();

	/**
	 * Synchronously loads an RPGItem subclass, this can hitch but is useful when you cannot wait for an async load
	 * This does not maintain a reference to the item so it will garbage collect if not loaded some other way
	 *
	 * @param PrimaryAssetId The asset identifier to load
	 * @param bDisplayWarning If true, this will log a warning if the item failed to load
	 */
	UTDItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};