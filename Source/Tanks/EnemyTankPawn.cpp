// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTankPawn.h"

#include "BaseHealthWidget.h"
#include "EnemyAIController.h"
#include "LevelTrigger.h"
#include "Particles/ParticleSystemComponent.h"


AEnemyTankPawn::AEnemyTankPawn()
{
	HealthWidget = CreateDefaultSubobject<UWidgetComponent>("HealthWidget");
	HealthWidget->SetWidgetClass(HealthWidgetClass);
	HealthWidget->SetupAttachment(BodyMesh);
}


void AEnemyTankPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
}

void AEnemyTankPawn::OnHealthChanged(float CurrentHealth)
{
	Cast<UBaseHealthWidget>(HealthWidget->GetWidget())->changeHealthPercent(CurrentHealth, HealthComponent->MaxHealth);
}

void AEnemyTankPawn::OnDeath()
{
	//DestructionEffect->ActivateSystem();
	GetWorldTimerManager().SetTimer(TimerBeforeDeath, this, &AEnemyTankPawn::onDeathAfterDestructionEffect, 0.5, false);
}

void AEnemyTankPawn::onDeathAfterDestructionEffect()
{
	Destroy();
	GetWorldTimerManager().ClearTimer(TimerBeforeDeath);
	
	if (LevelTrigger)
		LevelTrigger->SetActive(true);
}

