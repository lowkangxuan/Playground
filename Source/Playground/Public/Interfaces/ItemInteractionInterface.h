// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UItemInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class PLAYGROUND_API IItemInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetPickedup(bool bPickedup);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HighlightItem(bool bHighlight);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ConstraintPhysics();
};
