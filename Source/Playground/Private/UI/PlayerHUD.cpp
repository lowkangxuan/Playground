// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"

UCommonActivatableWidget* UPlayerHUD::PushWidgetToHud_Implementation(TSubclassOf<UCommonActivatableWidget> Class, bool bWithBlur, float TransitionDuration)
{
	return nullptr;
}

void UPlayerHUD::SetDefultHUDVitals_Implementation(const float BaseHealth, const float BaseArmor)
{
}

void UPlayerHUD::UpdateHUDVitals_Implementation(const float NewHealth, const float NewArmor)
{
}
