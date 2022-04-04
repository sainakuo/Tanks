// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTankPawn.h"
#include "HealthComponent.h"
#include "LevelTrigger.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "BaseFactory.generated.h"

UCLASS()
class TANKS_API ABaseFactory : public AActor, public IDamageTarget
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABaseFactory();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UArrowComponent* SpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Factory")
	TArray<ATargetPoint*> Waypoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Factory")
	TSubclassOf<AEnemyTankPawn> TankClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Factory")
	int MaxTanks = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Factory")
	int SpawnInterval = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Factory")
	ALevelTrigger* LevelTrigger;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* TankSpawnEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* DestructionEffect;

	virtual void TakeDamage(FDamageData Damage) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void OnTankSpawnTick();
	void onDeath();
	void onDeathAfterDestructionEffect();

	int TankSpawned = 0;
	FTimerHandle TimerHandler;
	FTimerHandle TimerBeforeDeath;

};
