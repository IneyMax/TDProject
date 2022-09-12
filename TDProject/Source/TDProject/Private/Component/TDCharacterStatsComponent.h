// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDCharacterStatsComponent.generated.h"

/** Delegate called when an Health Changed */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, CurrenHealth, float, MaxHealth);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedNative, float, float);

/** Delegate called when an Take Damage */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTakeDamage, float, DamageSize, AActor*, DamageSource);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTakeDamageNative, float, AActor*);

UCLASS( ClassGroup=(CharacterStats), meta=(BlueprintSpawnableComponent) )
class UTDCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDCharacterStatsComponent();

private:
	UPROPERTY(EditAnywhere, Category = CharacterStats)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = CharacterStats)
	float MaxHealth;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void GetHealthStats (float &CurrenHP, float &MaxHP) const;

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void TakeDamage(float DamageSize, AActor* DamageSource);

	UFUNCTION(BlueprintCallable, Category = CharacterStats)
	void HealthRecover(float RecoverableHealth);

	/** Delegate called when an Health Changed */
	UPROPERTY(BlueprintAssignable, Category = CharacterStats)
	FOnHealthChanged OnHealthChanged;

	/** Native version above, called before BP delegate */
	FOnHealthChangedNative OnHealthChangedNative;

	UPROPERTY(BlueprintAssignable, Category = CharacterStats)
	FOnTakeDamage OnTakeDamage;

	/** Native version above, called before BP delegate */
	FOnTakeDamageNative OnTakeDamageNative;
	
	/** Called after the inventory was changed and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = CharacterStats)
	void CallHealthChanged(float CurrentHP, float MaxHP);

	/** Called after the inventory was changed and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = CharacterStats)
	void CallTakeDamage(float DamageSize, AActor* DamageSource);

	void NotifyHealthChanged(float CurrentHP, float MaxHP);
	void NotifyTakeDamage(float DamageSize, AActor* DamageSource);
};

