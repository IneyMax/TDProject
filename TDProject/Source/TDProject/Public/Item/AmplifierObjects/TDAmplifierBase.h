#pragma once

#include "CoreMinimal.h"
#include "Interface/IAmplifier.h"
#include "UObject/Object.h"
#include "TDAmplifierBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TDPROJECT_API UTDAmplifierBase : public UObject, public IIAmplifier
{
	GENERATED_BODY()
	
public:
	virtual void UseAmplifier_Implementation() override;
};
