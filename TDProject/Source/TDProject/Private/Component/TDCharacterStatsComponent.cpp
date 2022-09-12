#include "Component/TDCharacterStatsComponent.h"

#include <string>

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "TDProject/TDProject.h"

UTDCharacterStatsComponent::UTDCharacterStatsComponent()
{
}

void UTDCharacterStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTDCharacterStatsComponent::GetHealthStats(float &CurrenHP, float &MaxHP) const
{
	MaxHP = MaxHealth;
	CurrenHP = CurrentHealth;
}

void UTDCharacterStatsComponent::TakeDamage(float DamageSize, AActor* DamageSource)
{
	CurrentHealth = UKismetMathLibrary::Clamp((CurrentHealth - DamageSize), 0, MaxHealth);
	NotifyHealthChanged(CurrentHealth, MaxHealth);
	NotifyTakeDamage(DamageSize, DamageSource);
}

void UTDCharacterStatsComponent::HealthRecover(float RecoverableHealth)
{
	CurrentHealth = UKismetMathLibrary::Clamp((CurrentHealth + RecoverableHealth), 0, MaxHealth);
	NotifyHealthChanged(CurrentHealth, MaxHealth);
}

void UTDCharacterStatsComponent::NotifyHealthChanged(float CurrentHP, float MaxHP)
{
	OnHealthChangedNative.Broadcast(CurrentHP, MaxHP);
	OnHealthChanged.Broadcast(CurrentHP, MaxHP);

	CallHealthChanged(CurrentHP, MaxHP);
}

void UTDCharacterStatsComponent::NotifyTakeDamage(float DamageSize, AActor* DamageSource)
{
	OnTakeDamageNative.Broadcast(DamageSize, DamageSource);
	OnTakeDamage.Broadcast(DamageSize, DamageSource);

	CallTakeDamage(DamageSize, DamageSource);
}
