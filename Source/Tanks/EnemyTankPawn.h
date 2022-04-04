// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "EnemyTankPawn.generated.h"

class ALevelTrigger;
class ATargetPoint;
/**
 * 
 */
UCLASS()
class TANKS_API AEnemyTankPawn : public ATankPawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Move")
	TArray<ATargetPoint*> Waypoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Factory")
	ALevelTrigger* LevelTrigger;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	int Number = -1;

private:
	virtual void OnDeath() override;
	void onDeathAfterDestructionEffect();
	FTimerHandle TimerBeforeDeath;
};
