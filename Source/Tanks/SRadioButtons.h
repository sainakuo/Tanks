// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RadioButtonsWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32);
DECLARE_DELEGATE_OneParam(FOnCountChanged, int32);

class TANKS_API SRadioButtons : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRadioButtons)
	{}

	SLATE_ATTRIBUTE(int32, Count)

	SLATE_ATTRIBUTE(int32, CurrentIndex)

	SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style)

	SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged)
	
	SLATE_END_ARGS()

	FOnRadioButtonChanged OnRadioButtonChanged;

	FOnCountChanged OnCountChanged;
	
	TAttribute<int> Count = 1;

	int32 CurrentIndex = 0;

	TSharedPtr<SVerticalBox> Holder;

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	ECheckBoxState IsChecked(int32 InIndex) const;
	void OnCheckStateChanged(ECheckBoxState NewState, int32 InIndex);
	void OnCountChangedFun(int32 NewCount);
	TSharedRef<SWidget> CreateCheckBox(int32 InIndex, FString InText);

	void CreateVerticalBox(int32 SlotsCount);

	const FCheckBoxStyle* CheckBoxStyle = nullptr;
	const FTextBlockStyle* TextBlockStyle = nullptr;
	
};
