// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlaygroundPlayerController.generated.h"

class APlaygroundCharacter;
class AHudManager;
class UItemObject;

UCLASS()
class PLAYGROUND_API APlaygroundPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UFUNCTION(BlueprintCallable)
	void DropItem(UItemObject* ItemToDrop);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DisplayName="Get HUD Manager"))
	AHudManager* GetHudManager();
};
