// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtons.h"

void URadioButtons::ChangeCount(int32 NewCount)
{
	if (NewCount != Count)
	{
		Count = NewCount;
		RadioButtons->OnCountChanged.Execute(Count);
	}
}

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	RadioButtons.Reset();
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	RadioButtons = SNew(SRadioButtons)
	.OnRadioButtonChanged_UObject(this, &ThisClass::OnRadioButtonChangedFunc)
	.Count(Count)
	.CurrentIndex(CurrentIndex)
	.Style(&WidgetStyle);
	
	return RadioButtons.ToSharedRef();
}

void URadioButtons::OnRadioButtonChangedFunc(int32 NewSelectedButton)
{
	OnRadioButtonChanged.Broadcast(NewSelectedButton);
}
