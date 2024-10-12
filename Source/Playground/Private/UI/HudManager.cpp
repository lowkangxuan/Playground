// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HudManager.h"
#include "UI/PlayerHUD.h"

void AHudManager::BeginPlay()
{
	Super::BeginPlay();
	MainHUD = Cast<UPlayerHUD>(CreateWidget(GetWorld(), HudClass));
	MainHUD->AddToViewport();
}

UCommonActivatableWidget* AHudManager::UploadWidget_Implementation(TSubclassOf<UCommonActivatableWidget> Widget, bool bPauseTime, bool bWithBlur, float TransitionDuration)
{
	return nullptr;
}

void AHudManager::SetupVitalsUI(const float Health, const float Armor)
{
}