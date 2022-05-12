// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "MyCoreStyle.h"

void UMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (RadioButtons_test)
		RadioButtons_test->WidgetStyle = FMyCoreStyle::Get().GetWidgetStyle<FRadioButtonsStyle>("WS_RadioButtons");

	if (Button_play_ws1)
		Button_play_ws1->WidgetStyle =  FMyCoreStyle::Get().GetWidgetStyle<FButtonStyle>("WS_Button");

	if (Button_quit_ws1)
		Button_quit_ws1->WidgetStyle =  FMyCoreStyle::Get().GetWidgetStyle<FButtonStyle>("WS_Button");

	if (Button_select_projectile)
		Button_select_projectile->WidgetStyle =  FMyCoreStyle::Get().GetWidgetStyle<FButtonStyle>("WS_Button");

	if (Button_select_laser)
		Button_select_laser->WidgetStyle =  FMyCoreStyle::Get().GetWidgetStyle<FButtonStyle>("WS_Button");
	
	if (Button_menu)
		Button_menu->WidgetStyle =  FMyCoreStyle::Get().GetWidgetStyle<FButtonStyle>("WS_Button");

	if (Button_inventory)
		Button_inventory->WidgetStyle =  FMyCoreStyle::Get().GetWidgetStyle<FButtonStyle>("WS_Button");

	if (Button_ok)
		Button_ok->WidgetStyle =  FMyCoreStyle::Get().GetWidgetStyle<FButtonStyle>("WS_Button");
}
