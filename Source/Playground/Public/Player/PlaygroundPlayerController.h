// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlaygroundPlayerController.generated.h"

class APlaygroundCharacter;
class UItemObject;

UCLASS()
class PLAYGROUND_API APlaygroundPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DropItem(UItemObject* ItemToDrop);
};
