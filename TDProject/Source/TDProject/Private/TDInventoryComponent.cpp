// Fill out your copyright notice in the Description page of Project Settings.


#include "TDProject/Public/TDInventoryComponent.h"

#include "TDProjectCharacter.h"
#include "ItemData/TDItem.h"
#include "TDProject/TDProject.h"

// Sets default values for this component's properties
UTDInventoryComponent::UTDInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTDInventoryComponent::BeginPlay()
{
	for (auto Slot : ItemSlots)
	{
		SetSlottedItem(Slot, nullptr);
	}
	
	Super::BeginPlay();
}

bool UTDInventoryComponent::AddInventoryItem(UTDItem* NewItem, int32 ItemCount, bool bAutoSlot)
{
	bool bChanged = false;
	if (!NewItem)
	{
		UE_LOG(LogTDProject, Warning, TEXT("AddInventoryItem: Failed trying to add null item!"));
		return false;
	}

	if (ItemCount <= 0)
	{
		UE_LOG(LogTDProject, Warning, TEXT("AddInventoryItem: Failed trying to add item %s with negative count!"), *NewItem->GetName());
		return false;
	}

	// Find current item data, which may be empty
	FTDItemData OldData;
	GetInventoryItemData(NewItem, OldData);

	// Find modified data
	FTDItemData NewData = OldData;
	NewData.UpdateItemData(FTDItemData(ItemCount), NewItem->MaxCount);

	if (OldData != NewData)
	{
		// If data changed, need to update storage and call callback
		InventoryData.Add(NewItem, NewData);
		NotifyInventoryItemChanged(true, NewItem);
		bChanged = true;
	}

	if (bAutoSlot)
	{
		// Slot item if required
		bChanged |= FillEmptySlotWithItem(NewItem);
	}

	if (bChanged)
	{
		// If anything changed, write to save game
		SaveInventory();
		return true;
	}
	return false;
}

const TArray<FTDItemSlot> UTDInventoryComponent::GetItemSlots() const
{
	return ItemSlots;
}

bool UTDInventoryComponent::RemoveInventoryItem(int32 &NewCount, UTDItem* RemovedItem, int32 RemoveCount)
{
	if (!RemovedItem)
	{
		UE_LOG(LogTDProject, Warning, TEXT("RemoveInventoryItem: Failed trying to remove null item!"));
		return false;
	}

	// Find current item data, which may be empty
	FTDItemData NewData;
	GetInventoryItemData(RemovedItem, NewData);

	if (!NewData.IsValid())
	{
		// Wasn't found
		return false;
	}
	
	// If RemoveCount <= 0, delete all
	if (RemoveCount <= 0)
	{
		NewData.ItemCount = 0;
		NewCount = 0;
	}
	else
	{
		NewData.ItemCount -= RemoveCount;
		NewCount = NewData.ItemCount;
	}
	
	if (NewData.ItemCount > 0)
	{
		// Update data with new count
		InventoryData.Add(RemovedItem, NewData);
		for (TPair<FTDItemSlot, UTDItem*>& Pair : SlottedItems)
		{
			if (Pair.Value == RemovedItem)
			{
				NotifySlottedItemChanged(Pair.Key, Pair.Value);
			}
		}
	}
	else
	{
		// Remove item entirely, make sure it is unslotted
		InventoryData.Remove(RemovedItem);

		for (TPair<FTDItemSlot, UTDItem*>& Pair : SlottedItems)
		{
			if (Pair.Value == RemovedItem)
			{
				Pair.Value = nullptr;
				NotifySlottedItemChanged(Pair.Key, Pair.Value);
			}
		}
	}

	// If we got this far, there is a change so notify and save
	NotifyInventoryItemChanged(false, RemovedItem);

	SaveInventory();
	return true;
}

void UTDInventoryComponent::GetInventoryItems(TArray<UTDItem*>& Items, FPrimaryAssetType ItemType)
{
	for (const TPair<UTDItem*, FTDItemData>& Pair : InventoryData)
	{
		if (Pair.Key)
		{
			FPrimaryAssetId AssetId = Pair.Key->GetPrimaryAssetId();

			// Filters based on item type
			if (AssetId.PrimaryAssetType == ItemType || !ItemType.IsValid())
			{
				Items.Add(Pair.Key);
			}
		}	
	}
}

void UTDInventoryComponent::GetUnusedInventoryItems(TArray<UTDItem*>& Items, FPrimaryAssetType ItemType)
{
	for (const TPair<UTDItem*, FTDItemData>& Pair : InventoryData)
	{
		FPrimaryAssetId AssetId = Pair.Key->GetPrimaryAssetId();

		// Filters based on item type
		if (AssetId.PrimaryAssetType == ItemType || !ItemType.IsValid())
		{
			Items.Add(Pair.Key);
		}
	}
	
	for (const TPair<FTDItemSlot, UTDItem*> Pair: SlottedItems)
	{
		Items.Remove(Pair.Value);
	}
}


int32 UTDInventoryComponent::GetInventoryItemCount(UTDItem* Item) const
{
	const FTDItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		return FoundItem->ItemCount;
	}
	return 0;
}


bool UTDInventoryComponent::GetInventoryItemData(UTDItem* Item, FTDItemData& ItemData) const
{
	const FTDItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		ItemData = *FoundItem;
		return true;
	}
	ItemData = FTDItemData(0);
	return false;
}


bool UTDInventoryComponent::SetSlottedItem(FTDItemSlot ItemSlot, UTDItem* Item)
{
	if (ItemSlot.IsValid())
	{
		SlottedItems.Add(ItemSlot, Item);
		NotifySlottedItemChanged(ItemSlot, Item);
		if (IsValid(Item))
		{
			return true;
		}
	}
	return false;
}
/*{
	/*
	// Iterate entire inventory because we need to remove from old slot
	bool bFound = false;
	for (TPair<FTDItemSlot, UTDItem*>& Pair : SlottedItems)
	{
		if (Pair.Key == ItemSlot)
		{
			// Add to new slot
			bFound = true;
			Pair.Value = Item;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
		else if (Item != nullptr && Pair.Value == Item)
		{
			// If this item was found in another slot, remove it
			Pair.Value = nullptr;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
	}

	if (bFound)
	{
		SaveInventory();
		return true;
	}

	return false;
}*/


UTDItem* UTDInventoryComponent::GetSlottedItem(FTDItemSlot ItemSlot) const
{
	UTDItem* const* FoundItem = SlottedItems.Find(ItemSlot);

	if (FoundItem)
	{
		return *FoundItem;
	}
	return nullptr;
}


void UTDInventoryComponent::GetSlottedItems(TArray<UTDItem*>& Items, FPrimaryAssetType ItemType)
{
	for (TPair<FTDItemSlot, UTDItem*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == ItemType || !ItemType.IsValid())
		{
			Items.Add(Pair.Value);
		}
	}
}

void UTDInventoryComponent::GetSlottedItemsMap(TMap<FTDItemSlot, UTDItem*> &ItemsBySlot, FPrimaryAssetType ItemType)
{
	for (TPair<FTDItemSlot, UTDItem*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == ItemType || !ItemType.IsValid())
		{
			ItemsBySlot.Add(Pair);
		}
	}
}

void UTDInventoryComponent::FillEmptySlots()
{
	bool bShouldSave = false;
	for (const TPair<UTDItem*, FTDItemData>& Pair : InventoryData)
	{
		bShouldSave |= FillEmptySlotWithItem(Pair.Key);
	}

	if (bShouldSave)
	{
		SaveInventory();
	}
}


bool UTDInventoryComponent::SaveInventory()
{
	return false;
}


bool UTDInventoryComponent::LoadInventory()
{
	return false;
}

bool UTDInventoryComponent::FillEmptySlotWithItem(UTDItem* NewItem)
{
	// Look for an empty item slot to fill with this item
	FPrimaryAssetType NewItemType = NewItem->GetPrimaryAssetId().PrimaryAssetType;
	FName NewItemUniqueTag = NewItem->UniqueTag;
	FTDItemSlot EmptySlot;
	for (TPair<FTDItemSlot, UTDItem*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == NewItemType && Pair.Key.UniqueTag == NewItemUniqueTag)
		{
			if (Pair.Value == NewItem)
			{
				// Item is already slotted
				return false;
			}
			else if (Pair.Value == nullptr)
			{
				// We found an empty slot worth filling
				EmptySlot = Pair.Key;
			}
		}
	}

	if (EmptySlot.IsValid())
	{
		SlottedItems[EmptySlot] = NewItem;
		NotifySlottedItemChanged(EmptySlot, NewItem);
		return true;
	}

	return false;
}

void UTDInventoryComponent::NotifyInventoryItemChanged(bool bAdded, UTDItem* Item)
{
	// Notify native before blueprint
	OnInventoryItemChangedNative.Broadcast(bAdded, Item);
	OnInventoryItemChanged.Broadcast(bAdded, Item);

	// Call BP update event
	InventoryItemChanged(bAdded, Item);
}

void UTDInventoryComponent::NotifySlottedItemChanged(FTDItemSlot ItemSlot, UTDItem* Item)
{
	// Notify native before blueprint
	OnSlottedItemChangedNative.Broadcast(ItemSlot, Item);
	OnSlottedItemChanged.Broadcast(ItemSlot, Item);

	// Call BP update event
	SlottedItemChanged(ItemSlot, Item);
}

void UTDInventoryComponent::NotifyInventoryLoaded()
{
	// Notify native before blueprint
	OnInventoryLoadedNative.Broadcast();
	OnInventoryLoaded.Broadcast();
}




