#pragma once

#include "CoreMinimal.h"
#include "TDProjectTypes.h"
#include "Components/ActorComponent.h"
#include "ItemData/TDItem.h"
#include "TDProject/TDProjectTypes.h"
#include "TDInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDPROJECT_API UTDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	/** Map of all items owned by this player, from definition to data */
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	TMap<UTDItem*, FTDItemData> InventoryData;

	/** Map of slot, from type/num to item, initialized from ItemSlotsPerType on RPGGameInstanceBase */
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	TMap<FTDItemSlot, UTDItem*> SlottedItems;

	/** Number of slots for each type of item */
	UPROPERTY(EditAnywhere, Category = Inventory)
	TArray<FTDItemSlot> ItemSlots;

public:
	/** Delegate called when an inventory item has been added or removed */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryItemChanged OnInventoryItemChanged;

	/** Native version above, called before BP delegate */
	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	/** Delegate called when an inventory slot has changed */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSlottedItemChanged OnSlottedItemChanged;

	/** Native version above, called before BP delegate */
	FOnSlottedItemChangedNative OnSlottedItemChangedNative;

	/** Delegate called when the inventory has been loaded/reloaded */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryLoaded OnInventoryLoaded;

	/** Native version above, called before BP delegate */
	FOnInventoryLoadedNative OnInventoryLoadedNative;

	/** Adds a new inventory item, will add it to an empty slot if possible.
	 *If the item supports count you can add more than one count.
	 *It will also update the level when adding if required */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddInventoryItem(UTDItem* NewItem, int32 ItemCount = 1, bool bAutoSlot = true);

	/** Called after the inventory was changed and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void InventoryItemChanged(bool bAdded, UTDItem* Item);

	/** Called after an item was equipped and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void SlottedItemChanged(FTDItemSlot ItemSlot, UTDItem* Item);
	
	UFUNCTION(BlueprintCallable, Category = Inventory)
	const TArray<FTDItemSlot> GetItemSlots() const;
	
	/** Remove an inventory item, will also remove from slots. A remove count of <= 0 means to remove all copies */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveInventoryItem(int32 &NewCount, UTDItem* RemovedItem, int32 RemoveCount = 1);

	/** Returns all inventory items of a given type. If none is passed as type it will return all */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetInventoryItems(TArray<UTDItem*>& Items, FPrimaryAssetType ItemType);

	/** Returns all unused inventory items of a given type. If none is passed as type it will return all */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetUnusedInventoryItems(TArray<UTDItem*>& Items, FPrimaryAssetType ItemType);

	/** Returns number of instances of this item found in the inventory. This uses count from GetItemData */
	UFUNCTION(BlueprintPure, Category = Inventory)
	int32 GetInventoryItemCount(UTDItem* Item) const;

	/** Returns the item data associated with an item. Returns false if none found */
	UFUNCTION(BlueprintPure, Category = Inventory)
	bool GetInventoryItemData(UTDItem* Item, FTDItemData& ItemData) const;

	/** Sets slot to item, will remove from other slots if necessary. If passing null this will empty the slot */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SetSlottedItem(FTDItemSlot ItemSlot, UTDItem* Item);

	/** Returns item in slot, or null if empty */
	UFUNCTION(BlueprintPure, Category = Inventory)
	UTDItem* GetSlottedItem(FTDItemSlot ItemSlot) const;

	/** Returns all slotted items of a given type. If none is passed as type it will return all */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetSlottedItems(TArray<UTDItem*>& Items, FPrimaryAssetType ItemType);

	/** Returns all slotted items of a given type. If none is passed as type it will return all */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetSlottedItemsMap(TMap<FTDItemSlot, UTDItem*> &ItemsBySlot, FPrimaryAssetType ItemType);

	/** Fills in any empty slots with items in inventory */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void FillEmptySlots();

	/** Manually save the inventory, this is called from add/remove functions automatically */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SaveInventory();

	/** Loads inventory from save game on game instance, this will replace arrays */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool LoadInventory();

protected:
	/** Auto slots a specific item, returns true if anything changed */
	bool FillEmptySlotWithItem(UTDItem* NewItem);

	/** Calls the inventory update callbacks */
	void NotifyInventoryItemChanged(bool bAdded, UTDItem* Item);
	void NotifySlottedItemChanged(FTDItemSlot ItemSlot, UTDItem* Item);
	void NotifyInventoryLoaded();

	/** Called when a global save game as been loaded */
	//void HandleSaveGameLoaded(URPGSaveGame* NewSaveGame);
};
