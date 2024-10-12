// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CommonActivatableWidget.h"
#include "HudManager.generated.h"

class UPlayerHUD;



UCLASS()
class PLAYGROUND_API AHudManager : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta=(DisplayName="HUD Class"))
	TSubclassOf<UPlayerHUD> HudClass;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerHUD> MainHUD;

protected:
	virtual void BeginPlay() override;

public:
	// Pushes a common widget into the stack in the main player HUD
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UCommonActivatableWidget* UploadWidget(TSubclassOf<UCommonActivatableWidget> Widget, bool bPauseTime, bool bWithBlur, float TransitionDuration = 0.1f);

	UFUNCTION(BlueprintCallable)
	void SetupVitalsUI(const float Health, const float Armor);
};
