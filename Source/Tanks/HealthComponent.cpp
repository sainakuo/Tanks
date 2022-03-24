// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::TakeDamage(FDamageData Damage)
{
	float prevHealth = CurrentHealth;
	
	CurrentHealth-= Damage.DamageValue;
	
	if (CurrentHealth < 0)
		CurrentHealth = 0;

	if (!FMath::IsNearlyEqual(prevHealth, CurrentHealth))
	{
		if (OnHealthChanged.IsBound())
			OnHealthChanged.Broadcast(CurrentHealth);
	}

	if (FMath::IsNearlyZero(CurrentHealth))
	{
		if (OnDeath.IsBound())
			OnDeath.Broadcast();
	}
	
}

float UHealthComponent::GetHealth()
{
	return CurrentHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

}