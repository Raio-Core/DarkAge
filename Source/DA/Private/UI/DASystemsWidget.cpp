// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DASystemsWidget.h"

void UDASystemsWidget::SetWidgetController(UWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
