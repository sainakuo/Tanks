// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHealthWidget.h"
#include "Cannon.h"
#include "CommonShooter.h"
#include "DamageTarget.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class TANKS_API ATurret : public ACommonShooter, public IDamageTarget
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ATurret();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCapsuleComponent* Collision;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire Params")
	float TargetingSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire Params")
	float TargetingRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire Params")
	int AimSlack = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* RangeSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	TSubclassOf<UBaseHealthWidget> HealthWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UWidgetComponent* HealthWidget;

	virtual void TakeDamage(FDamageData Damage) override;

	void OnHealthChanged(float CurrentHealth);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);

	UFUNCTION()	
	void OnEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TArray<AActor*> OtherActors;
	TWeakObjectPtr<AActor> Target;

	void FindNextTarget();
	void Fire();
	void Targeting();
	void OnDeath();

};
