// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DASystemsWidget.generated.h"

class UWidgetController;
/**
 * 
 */
UCLASS()
class DA_API UDASystemsWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetController> WidgetController;
	
public:
	
	void SetWidgetController(UWidgetController* InWidgetController);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
