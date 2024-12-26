// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/UICardWidget.h"
#include "CommonTextBlock.h"
#include "Components/Border.h"
#include "Components/WidgetSwitcher.h"

void UUICardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//if(IsDesignTime()) return;
	//ProgressMat = UMaterialInstanceDynamic::Create(Cast<UMaterialInterface>(InputProgress->Background.GetResourceObject()), this);
	//InputProgress->SetBrushFromMaterial(ProgressMat);
}

void UUICardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUICardWidget::SetTitle_Implementation(const FText& NewTitle)
{
	Title->SetText(NewTitle);
}

void UUICardWidget::SetSubTitle_Implementation(const FText& NewSubTitle)
{
	UE_LOG(LogTemp, Log, TEXT("%hs"), NewSubTitle.IsEmpty() ? "true" : "false");
	if (NewSubTitle.IsEmpty())
	{
		SubTitle->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	SubTitle->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SubTitle->SetText(NewSubTitle);
}

void UUICardWidget::SetDescription_Implementation(const FText& NewDescription)
{
	Description->SetText(NewDescription);
}

void UUICardWidget::ShowProgressBar(bool bShow)
{
	InputTypeSwitcher->SetActiveWidgetIndex(bShow ? 1 : 0);
	//ProgressMat = UMaterialInstanceDynamic::Create(Cast<UMaterialInterface>(InputProgress->Background.GetResourceObject()), this);
	//InputProgress->SetBrushFromMaterial(ProgressMat);
}
