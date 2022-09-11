// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDItem.generated.h"

UCLASS(Abstract, BlueprintType)
class TDPROJECT_API UTDItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	UTDItem()
		: MaxCount(1)
	{}

	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintGetter = GetItemType, Category = Item)
	FPrimaryAssetType ItemType;

	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	/** User-visible long description */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	/** Unique tag */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FName UniqueTag;
	
	/** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 MaxCount;

	/** Returns if the item is consumable (MaxCount <= 0)*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Item)
	bool IsConsumable() const;

	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintGetter, Category = Item)
	FPrimaryAssetType GetItemType() const;

	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
