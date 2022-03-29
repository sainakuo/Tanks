// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankPawn.h"
#include "TargetController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AEnemyAIController : public AAIController, public ITargetController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Move")
	FName WaypointTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Move", meta=(MekeEditWidget = true))
	TArray<FVector> PatrollingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI|Move")
	float MovementAccuracy = 100;


	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual FVector GetShootTarget() const override;

private:
	int32 CurrentPatrolPointIndex = 0;

	UPROPERTY()
	ATankPawn* TankPawn;

	TWeakObjectPtr<AActor> Target;
};
