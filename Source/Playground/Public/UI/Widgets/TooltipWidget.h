// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Structs/TooltipInfo.h"
#include "TooltipWidget.generated.h"

class UImage;
class UUICardWidget;

UCLASS()
class PLAYGROUND_API UTooltipWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UUICardWidget> CardWidget;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> IconImage;

	UPROPERTY(BlueprintReadOnly)
	FTooltipInfo TooltipInfo;

protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitInfo(const FTooltipInfo& Info);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateInputElapsedTime(float ElapsedTime);
};
