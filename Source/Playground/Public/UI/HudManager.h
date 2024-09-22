// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CommonActivatableWidget.h"
#include "HudManager.generated.h"

UCLASS(Abstract)
class PLAYGROUND_API AHudManager : public AHUD
{
	GENERATED_BODY()

public:
	

public:
	// Pushes a common widget into the stack in the main player HUD
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UCommonActivatableWidget* PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> Widget, bool bPauseTime);

	// Toggling Cheat Console
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleCheatConsole();
};
