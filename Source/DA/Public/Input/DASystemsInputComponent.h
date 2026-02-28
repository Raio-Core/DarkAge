// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAInputConfig.h"
#include "EnhancedInputComponent.h"
#include "DASystemsInputComponent.generated.h"

class UDAInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DA_API UDASystemsInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

private:
	

protected:

	virtual void BeginPlay() override;

public:
	
	UDASystemsInputComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityAction(UDAInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);

};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UDASystemsInputComponent::BindAbilityAction(UDAInputConfig* InputConfig, UserClass* Object, 
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);
	
	for (const FDAInputAction Action : InputConfig->DAInputActions)
	{
		if (IsValid(Action.InputAction) && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
		}
	}
}
