// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlaygroundGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API UPlaygroundGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	float SmallStorageSize = 64.0f;
	
	UPROPERTY(BlueprintReadOnly)
	float MediumStorageSize = 128.0f;
	
	UPROPERTY(BlueprintReadOnly)
	float LargeStorageSize = 192.0f;
};
