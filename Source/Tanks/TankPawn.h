// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoBox.h"
#include "Cannon.h"
#include "CommonShooter.h"
#include "DamageTarget.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "TankPawn.generated.h"


UCLASS()
class TANKS_API ATankPawn : public ACommonShooter, public IDamageTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	virtual void TakeDamage(FDamageData Damage) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	ACannon* CannonSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ACannon> CannonTypeSecond;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float MoveSpeed = 300;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float RotationSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float MovementAcceleration = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float RotationAcceleration = 0.1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
    float TurretAcceleration = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* DamageEffect;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* DestructionEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	class UUserWidget* GameOverWidget;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Move")
	FName WaypointTag;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float Scale);

	UFUNCTION()
	void RotateRight(float Scale);
	
	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void FireSpecial();
	
	UFUNCTION()
	void StartFireSeries();

	UFUNCTION()
	void ChangeCannon();

	virtual void Destroyed() override;

	UFUNCTION()
	void SetupCannon(bool CannonNumber);
	
	UFUNCTION()
	void ProjectilePlus(int num);

	virtual void PossessedBy(AController* NewController) override;

private:
	void MoveTank(float DeltaTime);
	void RotateTank(float DeltaTime);
	void RotateCannon(float DeltaTime);
	void PrintProjectile();
	virtual void OnDeath();
	void OnHealthChanged(float CurrentHealth);
	
	float MoveScaleCurrent = 0;
	float MoveScaleTarget = 0;

	float RotateScaleCurrent = 0;
	float RotateScaleTarget = 0;

	bool CurrentCannon = 0; // 0 - Cannon, 1 - CannonSecond
	
	UPROPERTY()
	class ATankPlayerController* TankController;
	
};
