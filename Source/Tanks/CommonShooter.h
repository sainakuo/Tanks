// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CommonShooter.generated.h"

class UHealthComponent;
class ACannon;
class UArrowComponent;
UCLASS()
class TANKS_API ACommonShooter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACommonShooter();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* BodyMesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UArrowComponent* CannonPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	TSubclassOf<ACannon> CannonClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	ACannon* Cannon;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;
	
};
