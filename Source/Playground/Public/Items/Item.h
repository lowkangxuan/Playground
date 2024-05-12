// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Item.generated.h"

class UItemDataAsset;

UCLASS(Abstract, Blueprintable)
class PLAYGROUND_API UItem : public UObject
{
	GENERATED_BODY()

public:
	TObjectPtr<UItemDataAsset> Data;
};
