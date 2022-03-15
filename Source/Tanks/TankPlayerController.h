// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ATankPawn* TankPawn;
	FVector MouseWorldPosition;

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMouseWorldPosition() const;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Scale);
	void RotateRight(float Scale);
	void OnShoot();
	void FireSpecial();
	void StartFireSeries();
	void ChangeCannon();

};
