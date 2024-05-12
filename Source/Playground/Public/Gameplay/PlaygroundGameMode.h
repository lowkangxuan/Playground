// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PlaygroundGameMode.generated.h"

UENUM()
enum EInputModes
{
	GameAndUI,
	OnlyGame,
	OnlyUI
};

UCLASS()
class PLAYGROUND_API APlaygroundGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInputModeAndPauseState(EInputModes InputMode, bool bSetGamePause = false);
};
