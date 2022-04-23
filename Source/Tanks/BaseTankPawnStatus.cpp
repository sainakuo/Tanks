// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTankPawnStatus.h"

void UBaseTankPawnStatus::changeHealthPercent(float CurrentHealth, float MaxHealth)
{
	currentHealthPercent = CurrentHealth/MaxHealth;

	HealthBar->SetPercent(currentHealthPercent);

	if (currentHealthPercent <= 0.5)
	{
		HealthBar->SetFillColorAndOpacity(FColor::Red);
	}
}

void UBaseTankPawnStatus::ChangeTextTotalProjectileCount(int Count)
{
	TextTotalProjectileCount->SetText(FText::FromString(FString::Printf(TEXT("%d"),Count)));
}

void UBaseTankPawnStatus::ChangeTextTotalTraceCount(int Count)
{
	TextTotalTraceCount->SetText(FText::FromString(FString::Printf(TEXT("%d"),Count)));
}
