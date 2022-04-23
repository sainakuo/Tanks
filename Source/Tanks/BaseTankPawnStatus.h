// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "BaseTankPawnStatus.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UBaseTankPawnStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTextBlock* TextHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTextBlock* TextTotalProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TextTotalProjectileCount;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTextBlock* TextTotalTrace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TextTotalTraceCount;

	void changeHealthPercent(float CurrentHealth, float MaxHealth);
	void ChangeTextTotalProjectileCount(int Count);
	void ChangeTextTotalTraceCount(int Count);

private:
	float currentHealthPercent = 1;
};
