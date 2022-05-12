// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtonsWidgetStyle.h"

FRadioButtonsStyle::FRadioButtonsStyle()
{

	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("RadioButton");
	TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalUnderlinedText");
}

FRadioButtonsStyle::~FRadioButtonsStyle()
{
}

const FName FRadioButtonsStyle::TypeName(TEXT("FRadioButtonsStyle"));

const FRadioButtonsStyle& FRadioButtonsStyle::GetDefault()
{
	static FRadioButtonsStyle Default;
	return Default;
}

void FRadioButtonsStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{

	FSlateWidgetStyle::GetResources(OutBrushes);

	CheckBoxStyle.GetResources(OutBrushes);

	TextBlockStyle.GetResources(OutBrushes);
	
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

