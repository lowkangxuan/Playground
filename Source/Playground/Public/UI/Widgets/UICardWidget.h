// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UICardWidget.generated.h"

class UBorder;
class UWidgetSwitcher;
class UCommonTextBlock;

UCLASS()
class PLAYGROUND_API UUICardWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UMaterialInstanceDynamic> ProgressMat;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> Title;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> SubTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> Description;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> InputTypeSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> InputProgress;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTitle(const FText& NewTitle);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetSubTitle(const FText& NewSubTitle);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetDescription(const FText& NewDescription);

	UFUNCTION(BlueprintCallable)
	void ShowProgressBar(bool bShow);
};
