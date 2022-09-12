// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IAmplifier.generated.h"


UINTERFACE(Blueprintable, MinimalAPI)
class UIAmplifier : public UInterface
{
	GENERATED_BODY()
};

/* Amplifiers Interface */
class TDPROJECT_API IIAmplifier
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=IAmplifier)
	void UseAmplifier();
};
