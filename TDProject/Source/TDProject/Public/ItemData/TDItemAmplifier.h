// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItem.h"
#include "Item/AmplifierObjects/TDAmplifier.h"
#include "TDItemAmplifier.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TDPROJECT_API UTDItemAmplifier : public UTDItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Amplifier)
	TSubclassOf<UTDAmplifier> AmplifierClass;
};
