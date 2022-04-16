// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTankPawn.h"

#include "EnemyAIController.h"
#include "LevelTrigger.h"
#include "Particles/ParticleSystemComponent.h"

void AEnemyTankPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Tank Created %d"), Number));
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

