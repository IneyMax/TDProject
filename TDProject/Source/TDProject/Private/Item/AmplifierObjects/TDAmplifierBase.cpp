// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AmplifierObjects/TDAmplifierBase.h"

void UTDAmplifierBase::UseAmplifier_Implementation()
{
	if (!this->GetOuter())
	{
		return;
	}
	//Cast<AActor>(this->GetOuter())->GetComponentByClass();
}
