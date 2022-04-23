// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTarget.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_EVENT(UHealthComponent, FDieEvent);

	DECLARE_EVENT_OneParam(UHealthComponent, FHealthChanged, float);

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	void TakeDamage(FDamageData Damage);
	
	float GetHealth();

	FDieEvent OnDeath;

	FHealthChanged OnHealthChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 10;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;

public:	
	
};
