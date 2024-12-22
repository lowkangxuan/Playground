// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

class UItemDataAsset;

UCLASS(Blueprintable, BlueprintType)
class PLAYGROUND_API UItemObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Transient)
	TObjectPtr<UItemDataAsset> ItemData;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTexture2D* GetIcon();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector2D GetGridSize();
};
