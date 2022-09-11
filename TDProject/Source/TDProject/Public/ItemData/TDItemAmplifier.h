// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItem.h"
#include "Item/AAmplifier/TDAmplifierBase.h"
#include "TDItemAmplifier.generated.h"

/**
 * 
 */
UCLASS()
class TDPROJECT_API UTDItemAmplifier : public UTDItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Amplifier)
	TSubclassOf<ATDAmplifierBase> AmplifierClass;
};