// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDInventoryComponent.h"
#include "GameFramework/Actor.h"
#include "ItemData/TDItemAmmo.h"
#include "TDWeaponBase.generated.h"

UCLASS()
class TDPROJECT_API ATDWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	ATDWeaponBase ();
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UTDItemAmmo *AmmoItem;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FTDItemSlot AmmoSlot;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSubclassOf<ATDBulletBase> BulletClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetAmmo (UTDItem *Item);
};
