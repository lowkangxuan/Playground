// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "TooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API UTooltipWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateInfo(const UTexture2D* ItemIcon, const FText& ItemName, const FText& ItemDesc);
	
};
