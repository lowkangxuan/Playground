// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UICardWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API UUICardWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTitle(const FText& NewTitle);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetDescription(const FText& NewDescription);
};
