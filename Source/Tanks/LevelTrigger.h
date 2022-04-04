// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "LevelTrigger.generated.h"

class UPointLightComponent;
UCLASS()
class TANKS_API ALevelTrigger : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ALevelTrigger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	USpotLightComponent* InactiveLight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	USpotLightComponent* ActiveLight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Level");
	bool isActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Level");
	FName LevelName;

	UFUNCTION()
	void SetActive(bool Active);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapTrigger(UPrimitiveComponent* Component, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int I, bool bArg, const FHitResult& HitResult);

};
