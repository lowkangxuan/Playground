// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PlayerHUD.generated.h"

class UCommonActivatableWidget;
/**
 * 
 */
UCLASS()
class PLAYGROUND_API UPlayerHUD : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(DisplayName="Push Widget To HUD"))
	UCommonActivatableWidget* PushWidgetToHud(TSubclassOf<UCommonActivatableWidget> Class, bool bWithBlur, float TransitionDuration);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(DisplayName="Set Default HUD Vitals"))
	void SetDefultHUDVitals(const float BaseHealth, const float BaseArmor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(DisplayName="Update HUD Vitals"))
	void UpdateHUDVitals(const float NewHealth, const float NewArmor);
};
