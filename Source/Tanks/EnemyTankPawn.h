// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHealthWidget.h"
#include "TankPawn.h"
#include "Components/WidgetComponent.h"
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

	AEnemyTankPawn();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Move")
	TArray<ATargetPoint*> Waypoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Factory")
	ALevelTrigger* LevelTrigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TSubclassOf<UBaseHealthWidget> HealthWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UWidgetComponent* HealthWidget;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void OnHealthChanged(float CurrentHealth) override;

	int Number = -1;

private:
	virtual void OnDeath() override;
	void onDeathAfterDestructionEffect();
	FTimerHandle TimerBeforeDeath;
};
