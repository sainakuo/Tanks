// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoBox.h"
#include "Cannon.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "TankPawn.generated.h"

UCLASS()
class TANKS_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* BodyMesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UArrowComponent* CannonPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ACannon> CannonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ACannon> CannonTypeSecond;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	ACannon* Cannon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	ACannon* CannonSecond;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float MoveSpeed = 100;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float RotationSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float MovementAcceleration = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
	float RotationAcceleration = 0.1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Speed")
    float TurretAcceleration = 0.1;

public:	
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

private:
	void MoveTank(float DeltaTime);
	void RotateTank(float DeltaTime);
	void RotateCannon(float DeltaTime);
	void PrintProjectile();
	void SetProjectileCount();
	
	float MoveScaleCurrent = 0;
	float MoveScaleTarget = 0;

	float RotateScaleCurrent = 0;
	float RotateScaleTarget = 0;

	bool CurrentCannon = 0; // 0 - Cannon, 1 - CannonSecond

	class ATankPlayerController* TankController;
	
};
