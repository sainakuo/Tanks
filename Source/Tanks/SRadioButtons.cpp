// Fill out your copyright notice in the Description page of Project Settings.


#include "SRadioButtons.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRadioButtons::Construct(const FArguments& InArgs)
{
	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;
	
	Count = InArgs._Count;

	CheckBoxStyle = &InArgs._Style->CheckBoxStyle;

	TextBlockStyle = &InArgs._Style->TextBlockStyle;

	int32 SlotsNum = Count.Get();
	
	CreateVerticalBox(SlotsNum);
	
	if (CurrentIndex < SlotsNum)
	{
		CurrentIndex = InArgs._CurrentIndex.Get();
	}

	OnCountChanged.BindSP(this, &SRadioButtons::OnCountChangedFun);
}

ECheckBoxState SRadioButtons::IsChecked(int32 InIndex) const
{
	return InIndex == CurrentIndex ? ECheckBoxState::Checked: ECheckBoxState::Unchecked;
}

void SRadioButtons::OnCheckStateChanged(ECheckBoxState NewState, int32 InIndex)
{
	if (NewState == ECheckBoxState::Checked)
	{
		CurrentIndex = InIndex;
		OnRadioButtonChanged.ExecuteIfBound(CurrentIndex);
	}
}

void SRadioButtons::OnCountChangedFun(int32 NewCount)
{
	Count = NewCount;
	
	Holder.Reset();
	
	CreateVerticalBox(NewCount);
	
}

TSharedRef<SWidget> SRadioButtons::CreateCheckBox(int32 InIndex, FString InText)
{
	//FCompositeFont MyCompFont = FCompositeFont(FName(TEXT("Roboto-Light")), "../../../Engine/Content/Slate/Fonts/Roboto-Light.ttf", EFontHinting::Default, EFontLoadingPolicy::LazyLoad);
	//TSharedPtr<const FCompositeFont> MyInCompositeFont(new FCompositeFont(MyCompFont)); 
	
	return SNew(SCheckBox)
	.IsChecked_Raw(this, &SRadioButtons::IsChecked, InIndex)
	.OnCheckStateChanged_Raw(this, &SRadioButtons::OnCheckStateChanged, InIndex)
	.Style(CheckBoxStyle)
	[
		SNew(STextBlock)
		.Text(FText::FromString(InText))
		.ColorAndOpacity(FColor::White)
		//.Font(FSlateFontInfo(MyInCompositeFont, 20))
		.TextStyle(TextBlockStyle)
	];

	
}

void SRadioButtons::CreateVerticalBox(int32 SlotsCount)
{
	Holder = SNew(SVerticalBox);
	
	for (int i = 0; i < SlotsCount; i++)
	{
		Holder->AddSlot()
		[
			CreateCheckBox(i, FString::Printf(TEXT("Option %d"), i+1))
		];
	}
	ChildSlot
	[
		Holder.ToSharedRef()
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
