// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHealthWidget.h"

void UBaseHealthWidget::changeHealthPercent(float CurrentHealth, float MaxHealth)
{
	currentHealthPercent = CurrentHealth/MaxHealth;

	HealthBar->SetPercent(currentHealthPercent);

	if (currentHealthPercent <= 0.5)
	{
		HealthBar->SetFillColorAndOpacity(FColor::Red);
	}
}

