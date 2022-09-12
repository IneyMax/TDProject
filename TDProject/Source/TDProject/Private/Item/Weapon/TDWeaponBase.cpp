// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/TDWeaponBase.h"
#include "Item/AmplifierObjects/TDAmplifierBase.h"


ATDWeaponBase::ATDWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATDWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATDWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDWeaponBase::SetAmmo (UTDItem *Item)
{
	if (IsValid(Item))
	{
		AmmoItem = Cast<UTDItemAmmo>(Item);
		BulletClass = AmmoItem->AmmoClass;
	}
	else
	{
		AmmoItem = nullptr;
		BulletClass = nullptr;
	}
}

void ATDWeaponBase::SetWeaponParams(FTDWeaponStats InWeaponStats)
{
	WeaponStats = InWeaponStats;
}
