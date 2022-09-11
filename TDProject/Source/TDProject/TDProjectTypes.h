// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TDProjectTypes.generated.h"

class UTDItem;

USTRUCT(BlueprintType)
struct TDPROJECT_API FTDItemSlot
{
	GENERATED_BODY()

	FTDItemSlot()
		: SlotNumber(-1)
	{}

	FTDItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}
	
	/** The type of items that can go in this slot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FPrimaryAssetType ItemType;

	/** The number of this slot, 0 indexed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 SlotNumber;

	/** Unique tag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FName UniqueTag;

	/** Equality operators */
	bool operator==(const FTDItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber && UniqueTag == Other.UniqueTag;
	}
	
	bool operator!=(const FTDItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** Implemented so it can be used in Maps/Sets */
	friend inline uint32 GetTypeHash(const FTDItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		Hash = HashCombine(Hash, GetTypeHash(Key.UniqueTag));
		return Hash;
	}

	/** Returns true if slot is valid */
	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}
};

/** Extra information about a URPGItem that is in a player's inventory */
USTRUCT(BlueprintType) 
struct TDPROJECT_API FTDItemData
{
	GENERATED_BODY()

	/** Constructor, default to count/level 1 so declaring them in blueprints gives you the expected behavior */
	FTDItemData()
		: ItemCount(1)
	{}

	FTDItemData(int32 InItemCount)
		: ItemCount(InItemCount)
	{}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	/** Equality operators */
	bool operator==(const FTDItemData& Other) const
	{
		return ItemCount == Other.ItemCount;
	}
	
	bool operator!=(const FTDItemData& Other) const
	{
		return !(*this == Other);
	}

	/** Returns true if count is greater than 0 */
	bool IsValid() const
	{
		return ItemCount > 0;
	}

	/** Append an item data, this adds the count and overrides everything else */
	void UpdateItemData(const FTDItemData& Other, int32 MaxCount)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
	}
};

/** Delegate called when an inventory item changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, UTDItem*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, UTDItem*);

/** Delegate called when the contents of an inventory slot change */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChanged, FTDItemSlot, ItemSlot, UTDItem*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedNative, FTDItemSlot, UTDItem*);

/** Delegate called when the entire inventory has been loaded, all items may have been replaced */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryLoaded);
DECLARE_MULTICAST_DELEGATE(FOnInventoryLoadedNative);


/** Delegate called when the save game has been loaded/reset */
/*
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoaded, URPGSaveGame*, SaveGame);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoadedNative, URPGSaveGame*);
*/