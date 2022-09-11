// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Ammo/TDBulletBase.h"


// Sets default values
ATDBulletBase::ATDBulletBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATDBulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

