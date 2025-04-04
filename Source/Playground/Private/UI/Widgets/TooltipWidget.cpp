// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/TooltipWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "UI/Widgets/UICardWidget.h"

void UTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTooltipWidget::InitInfo_Implementation(const FTooltipInfo& Info)
{
	TooltipInfo = Info;
	IconImage->SetBrushFromTexture(TooltipInfo.Icon);
	CardWidget->SetTitle(TooltipInfo.Title);
	CardWidget->SetSubTitle(TooltipInfo.SubTitle);
	CardWidget->SetDescription(TooltipInfo.Description);
	CardWidget->ShowProgressBar(TooltipInfo.InteractionDelay > 0);
}

void UTooltipWidget::UpdateInputElapsedTime_Implementation(float ElapsedTime)
{
	CardWidget->ProgressMat->SetScalarParameterValue("Progress", ElapsedTime/TooltipInfo.InteractionDelay);
}