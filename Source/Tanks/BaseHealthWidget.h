// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "BaseHealthWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TANKS_API UBaseHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;

	void changeHealthPercent(float CurrentHealth, float MaxHealth);

private:
	float currentHealthPercent = 1;
	
};
