// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UENUM()
enum class ECannonType: uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use projectile" ),
	FireTrace = 1 UMETA (DisplayName = "Use trace")
};

UCLASS()
class TANKS_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* ShootEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int ProjectileCount = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	int FireCountInSeries = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRateSeries = 4;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	TSubclassOf<AProjectile> ProjectileClassSpecial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float LaserDamage = 4;
	
	void Shoot();

	void FireSpecial();

	void StartFireSeries();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bReadyToShoot = true;
	void ResetShootState();
	FTimerHandle TimerHandle;
	FTimerHandle TimerHandleForSeries;
	void StartShootTimer();
	bool bProjectileStock = true;
	void ProjectileDecrease();
	
	bool bStartToShootSeries = false;
	void FireSeriesTick();
	int FireCountInSeriesLocal = FireCountInSeries;
	
};
